#include "DebugGrid.h"
#include <DxLib.h>

namespace My3dApp
{
    void DrawGrid(float groundSize, int divideNum)
    {
        /** */
        VECTOR start = VGet(0, 0, 0);

        /** */
        VECTOR end = VGet(0, 0, 0);

        /** ���̐F*/
        int lineColor = GetColor(0, 128, 0);

        /** �O���b�h���������͈͂̔����̕�*/
        float halfWidth = groundSize * 0.5f;

        /** �O���b�h���������Ԋu*/
        float addWidth = groundSize / (float)divideNum;

        /** �c��������*/
        start.z = -halfWidth;
        end.z = +halfWidth;
        for (int ix = 0; ix < divideNum + 1; ix++)
        {
            start.x= -halfWidth + ix * addWidth;
            end.x = -halfWidth + ix * addWidth;
            DrawLine3D(start, end, lineColor);
        }

        /** ����*/
        start.x = -halfWidth;
        end.x = +halfWidth;
        for (int iz = 0; iz < divideNum + 1; iz++)
        {
            start.z = -halfWidth + iz * addWidth;
            end.z = -halfWidth + iz * addWidth;
            DrawLine3D(start, end, lineColor);
        }
    }
}/** namespace My3dApp*/