#pragma once

namespace My3dApp
{
    class Shadow
    {
    private:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Shadow();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Shadow();

        // シャドウの唯一のインスタンス
        static Shadow* instance;

        // シャドウマップ
        static int shadowMap;

    public:
        /// <summary>
        /// インスタンスの生成
        /// </summary>
        static void CreateInstance();

        /// <summary>
        /// インスタンスの削除
        /// </summary>
        static void DeleteInstance();

        /// <summary>
        /// シャドウマップの取得
        /// </summary>
        /// <returns>シャドウマップ</returns>
        static int GetShadowMap() { return shadowMap; }
    };
}