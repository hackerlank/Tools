using System.IO;
using System.Text;

namespace FileArchiveToolTest
{
	class ArchiveHeader
	{
		public const uint ARCHIVETOOL_VERSION = 101100;

		public byte[] m_magic;			// 幻数
		public byte m_endian;				// 大小端
		public uint m_headerSize;		// 头部大小
		public uint m_version;			// 版本
		public uint m_fileCount;			// 文件总共数量

		public ArchiveHeader()
		{
			m_version = ARCHIVETOOL_VERSION;

			m_magic = new byte[4];
			m_magic[0] = (byte)'a';
			m_magic[1] = (byte)'s';
			m_magic[2] = (byte)'d';
			m_magic[3] = (byte)'f';

			m_endian = (byte)Endian.LITTLE_ENDIAN;		// 0 大端 1 小端
		}

		public void clear()
		{
			m_fileCount = 0;
			m_headerSize = 0;
		}

		public bool readArchiveFileHeader(FileStream fileHandle, MByteBuffer pMByteBuffer)
		{
			pMByteBuffer.clear ();
			fileHandle.Read(pMByteBuffer.dynBuff.buff, 0, 4);
			pMByteBuffer.length = 4;
			string magic = pMByteBuffer.readMultiByte(4, Encoding.UTF8);
			if (magic != "asdf")		// 检查 magic
			{
				return false;
			}

			pMByteBuffer.clear ();
			fileHandle.Read(pMByteBuffer.dynBuff.buff, 0, (int)calcArchiveHeaderSizeNoFileHeader() - 4);
			pMByteBuffer.length = calcArchiveHeaderSizeNoFileHeader() - 4;
			// 读取 endian 
			m_endian = pMByteBuffer.readByte ();
			pMByteBuffer.setEndian((Endian)m_endian);

			// 读取头部大小
			m_headerSize = pMByteBuffer.readUnsignedInt();

			// 读取版本
			m_version = pMByteBuffer.readUnsignedInt();
			// 读取文件数量
			m_fileCount = pMByteBuffer.readUnsignedInt();

			// 读取整个头
			pMByteBuffer.clear ();
			fileHandle.Read(pMByteBuffer.dynBuff.buff, 0, (int)(m_headerSize - calcArchiveHeaderSizeNoFileHeader()));
			pMByteBuffer.length = m_headerSize - calcArchiveHeaderSizeNoFileHeader ();

			return true;
		}

		public uint calcArchiveHeaderSizeNoFileHeader()
		{
			// 写入 magic 
			// 写入 endian 
			// 写入头部总共大小
			// 写入版本
			// 写入文件数量
			return (uint)m_magic.Length + sizeof(byte) + sizeof(uint) + sizeof(uint) + sizeof(uint);
		}
	}
}