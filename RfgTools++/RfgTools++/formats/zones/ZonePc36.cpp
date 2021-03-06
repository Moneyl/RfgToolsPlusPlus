#include "ZonePc36.h"
#include "common/filesystem/Path.h"
#include "common/filesystem/File.h"
#include "common/string/String.h"
#include "hashes/HashGuesser.h"
#include <BinaryTools/BinaryReader.h>
#include <filesystem>
#include <iostream>

//Reads header and object data from a zone file (rfgzone_pc or layer_pc)
void ZonePc36::Read(BinaryReader& reader)
{
    //Read and validate header
    reader.ReadToMemory(&Header, sizeof(ZonePcHeader36));
    if (Header.Signature != 1162760026) //Should equal ascii value for "ZONE"
        throw std::exception(("Error! Invalid zone file signature. Expected 1162760026, detected " + std::to_string(Header.Signature)).c_str());
    if (Header.Version != 36) //Only have seen and reversed version 36
        throw std::exception(("Error! Invalid zone file version. Expected 36, detected " + std::to_string(Header.Version)).c_str());

    //Todo: Determine what the other flag bits mean
    //Read relational data if it's useful
    hasRelationalData_ = (Header.DistrictFlags & 5) == 0;

    //Todo: Figure out how to interpret this data. Enable this if it's useful. See ZonePcRelationData36.h
    //reader.ReadToMemory(&RelationalData, sizeof(ZonePcRelationData36));
    if (hasRelationalData_)
        reader.Skip(87368); //For now we just skip it since it's not clear how to interpret that data yet

    //Don't read further if file has no objects
    if (Header.NumObjects == 0)
        return;

    //Read zone objects
    Objects.reserve(Header.NumObjects);
    for (u32 i = 0; i < Header.NumObjects; i++)
    {
        u64 pos = reader.Position();
        ZoneObject36& object = Objects.emplace_back();
        object.Read(reader);
    }

    //Guess zone district name
    auto result = HashGuesser::GuessHashOriginString(Header.DistrictHash);
    districtName_ = result ? result.value() : "unknown";
}

void ZonePc36::GenerateObjectHierarchy()
{
    const u32 InvalidHandle = 0xFFFFFFFF; //Todo: Make this a global constant somewhere
    if (Objects.size() <= 1)
        return;

    //Register top level objects as first pass (objects with no parent). Done in two steps since it's simpler
    for (auto& object : Objects)
    {
        //If has no parent then register as a top level object
        if (object.Parent == InvalidHandle)
        {
            auto& hierarchyNode = ObjectsHierarchical.emplace_back();
            hierarchyNode.Self = &object;
        }
    }

    //Register objects to their parents
    for (auto& object : Objects)
    {
        //Skip top level objects as they were handled in the first pass
        if (object.Parent == InvalidHandle)
            continue;

        //Find parent
        ZoneObjectNode36* maybeParent = GetTopLevelObject(object.Parent);
        //Todo: Search in other zones/files for parents and siblings + move this step into a different class. Likely need to check matching p_ and non p_ files
        //Make it a top level object if we can't find it's parent in this zone
        if (!maybeParent)
        {
            auto& hierarchyNode = ObjectsHierarchical.emplace_back();
            hierarchyNode.Self = &object;
            continue;
        }


        //Register with parent if not already done
        auto& parent = *maybeParent;
        parent.AddChildObjectIfUnique(&object);

        //Add siblings to parents if not already done
        ZoneObject36* currentObject = &object;
        while (currentObject->Sibling != InvalidHandle)
        {
            ZoneObject36* maybeSibling = GetObject(currentObject->Sibling);
            //Todo: Search in other zones/files for parents and siblings + move this step into a different class. Likely need to check matching p_ and non p_ files
            if (!maybeSibling)
            {
                //std::cout << "Warning in \"" << Name() << "\". Object " << currentObject->Handle << " could not find it's sibling with handle " << currentObject->Sibling << "\n";
                break;
            }

            currentObject = maybeSibling;
            parent.AddChildObjectIfUnique(currentObject);
        }
    }
}

bool ZonePc36::IsTopLevelObject(u32 handle)
{
    for (const auto& object : ObjectsHierarchical)
    {
        if (object.Self->Handle == handle)
            return true;
    }
    return false;
}

ZoneObjectNode36* ZonePc36::GetTopLevelObject(u32 handle)
{
    for (auto& object : ObjectsHierarchical)
    {
        if (object.Self->Handle == handle)
            return &object;
    }
    return nullptr;
}

ZoneObject36* ZonePc36::GetObject(u32 handle)
{
    for (auto& object : Objects)
    {
        if (object.Handle == handle)
            return &object;
    }
    return nullptr;
}

ZoneObject36* ZonePc36::GetSingleObject(const string& classname)
{
    //Todo: May be faster to hash the classname string first and compare that
    for (auto& object : Objects)
    {
        if (object.Classname == classname)
            return &object;
    }
    return nullptr;
}
