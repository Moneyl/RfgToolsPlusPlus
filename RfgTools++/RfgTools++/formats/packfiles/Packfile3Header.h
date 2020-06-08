#pragma once
#include "common/Typedefs.h"

class Packfile3Header
{
public:
    //Magic signature to identify packfiles. Should be 1367935694 | 0xCE0A8951
    u32 Signature = 0;
    //Format version. Should be 3
    u32 Version = 0;
    //Unused data section. Used by gibbed's unpacker so leaving it open for reading here
    char ShortName[65] = {};
    //Unused data section. Used by gibbed's unpacker so leaving it open for reading here
    char PathName[256] = {};
    //Alignment padding. Value does not matter
    u8 Pad1[3] = {};
    //Format flags. Describes the format and layout of the data block
    u32 Flags = 0;
    //Junk for our purposes. Set by game at runtime
    u8 Junk1[4] = {};
    //The number of subfiles in this packfile
    u32 NumberOfSubfiles = 0;
    //The total size in bytes of the packfile
    u32 FileSize = 0;
    //The size of the entry block in bytes. Includes padding bytes
    u32 EntryBlockSize = 0;
    //The size of the names block in bytes. Includes padding bytes
    u32 NameBlockSize = 0;
    //The size of the data block in bytes. Includes padding bytes. If the vpp is compressed this refers to the size after decompression
    u32 DataSize = 0;
    //The size of the data block compressed data in bytes. Includes padding bytes. Equals 0xFFFFFFFF if packfile isn't compressed
    u32 CompressedDataSize = 0;

    //Data following this for reference. Not in this struct since it's junk data or empty, and not used by user tooling so far.
    //12 bytes of junk data that we don't need. Set by the game at runtime
    //1668 bytes padding to align(2048)
};

//Required for the read technique used to work
static_assert(sizeof(Packfile3Header) == 364,
    "Error! sizeof(Packfile3Header) must equal 364 bytes. This data is loaded straight into memory and cast to this struct so it must be this size to work.");