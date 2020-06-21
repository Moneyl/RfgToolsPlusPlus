#pragma once
#include "common/Typedefs.h"

enum class AllocatorType : u8
{
    None = 0,
    World = 1,
    ChunkPreload = 2,
    EffectPreload = 3,
    EffectCutscene = 4,
    ItemPreload = 5,
    DecalPreload = 6,
    ClothSimPreload = 7,
    Tod = 8,
    MpEffectPreload = 9,
    MpItemPreload = 10,
    Player = 11,
    Human = 12,
    LargeWeapon = 13,
    SmallWeapon = 14,
    Vehicle = 15,
    LargeLayer = 16,
    SmallLayer = 17,
    HumanVoicePersona = 18,
    AlwaysLoadedHumanVoicePersona = 19,
    Audio = 20,
    Interface = 21,
    Fsm = 22,
    InterfaceStack = 23,
    InterfaceSlot = 24,
    InterfaceMpPreload = 25,
    InterfaceMpSlot = 26,
    MaterialEffect = 27,
    Permanent = 28,
    DlcEffectPreload = 29,
    DlcItemPreload = 30,
    NumAllocatorTypes = 31,
};

enum class ContainerType : u8
{
    None = 0,
    Glass = 1,
    EffectsEnv = 2,
    EffectsPreload = 3,
    EffectsDlc = 4,
    MpEffects = 5,
    LayerSmall = 6,
    LayerLarge = 7,
    Audio = 8,
    ClothSim = 9,
    Decals = 10,
    DecalsPreload = 11,
    Fsm = 12,
    Ui = 13,
    Env = 14,
    Chunk = 15,
    ChunkPreload = 16,
    Stitch = 17,
    World = 18,
    HumanHead = 19,
    Human = 20,
    Player = 21,
    Items = 22,
    ItemsPreload = 23,
    ItemsMpPreload = 24,
    ItemsDlc = 25,
    WeaponLarge = 26,
    WeaponSmall = 27,
    Skybox = 28,
    Vehicle = 29,
    VoicePersona = 30,
    AlwaysLoadedVoicePersona = 31,
    Foliage = 32,
    UiPeg = 33,
    MaterialEffect = 34,
    MaterialPreload = 35,
    SharedBackpack = 36,
    LandmarkLod = 37,
    GpsPreload = 38,
    NumContainerTypes = 39
};

enum class PrimitiveType : u8
{
    None = 0,
    Peg = 1,
    Chunk = 2,
    Zone = 3,
    Terrain = 4,
    StaticMesh = 5,
    CharacterMesh = 6,
    FoliageMesh = 7,
    Material = 8,
    ClothSim = 9,
    Vehicle = 10,
    VehicleAudio = 11,
    Vfx = 12,
    Wavebank = 13,
    FoleyBank = 14,
    MeshMorph = 15,
    VoicePersona = 16,
    AnimFile = 17,
    Vdoc = 18,
    LuaScript = 19,
    Localization = 20,
    TerrainHighLod = 21,
    LandmarkLod = 22,
    NumPrimitiveTypes = 23,
};