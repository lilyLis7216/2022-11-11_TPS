#pragma once

namespace My3dApp
{
    /** 当たり判定の形状の種類*/
    enum class CollisionType
    {
        Line,   /**< 線分*/
        Sphere, /**< 球*/
        Capsule,/**< カプセル*/
        Model,  /**< モデル（メッシュ）*/
    };
}/** namespace My3dApp*/