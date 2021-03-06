﻿using System;
using System.Collections.Generic;
using System.Text;

namespace FileArchiveToolTest
{
    /**
     *@brief 字节编码解码，大端小端
     */
    public static class ByteUtil
    {
        /**
         *@brief 检查大端小端
         */
        static public void checkEndian()
        {
            // 检测默认编码
            // 方法一
            //if (ByteArray.m_sEndian == Endian.NONE_ENDIAN)
            //{
            //    byte[] bt = System.BitConverter.GetBytes(1);
            //    if (bt[0] == 1)  // 数据的低位保存在内存的低地址中
            //    {
            //        ByteArray.m_sEndian = Endian.LITTLE_ENDIAN;
            //    }
            //    else
            //   {
            //        ByteArray.m_sEndian = Endian.BIG_ENDIAN;
            //    }
            //}
            // 方法二
            if(System.BitConverter.IsLittleEndian)
            {
				MByteBuffer.m_sEndian = Endian.LITTLE_ENDIAN;
            }
            else
            {
				MByteBuffer.m_sEndian = Endian.BIG_ENDIAN;
            }
        }

        // 两种编码的 string 字符串之间转换
        static public string convStr2Str(string srcStr, Encoding srcCharSet, Encoding destCharSet)
        {
            byte[] srcBytes = srcCharSet.GetBytes(srcStr);
            byte[] destBytes = Encoding.Convert(srcCharSet, destCharSet, srcBytes);
            string retStr;
            retStr = destCharSet.GetString(destBytes, 0, destBytes.Length);
            return retStr;
        }
    }
}