#include "WaveFile.h"

namespace Sand
{
	namespace Audio
	{
		WaveFile::WaveFile(short channelNumber, int sampleRate, int byteRate, short bitsPerSample, BYTE* data, int dataSize)
			: m_ChannelNumber(channelNumber), m_SampleRate(sampleRate), m_ByteRate(byteRate), m_BitsPerSample(bitsPerSample), m_Data(data), m_DataSize(dataSize)
		{ }

		WaveFile::~WaveFile()
		{
			delete m_Data;
		}

		WaveFile* WaveFile::Load(std::string path)
		{
			IO::FileStream* file = new IO::FileStream(path, IO::FileAccess::ReadBinary);
			IO::StreamReader reader(file);
			RIFF riff;
			reader.Read(&riff, 1, sizeof(RIFF));
			WaveFMT fmt;
			reader.Read(&fmt, 1, sizeof(WaveFMT));
			WaveSubChunk chunk;
			BYTE* data = NULL;
			int dataSize = 0;

			while (!reader.Peek())
			{
				reader.Read(&chunk, 1, sizeof(WaveSubChunk));
				if (!strcmp(chunk.ID, "data"))
				{
					dataSize = chunk.Size;
					data = new BYTE[dataSize];
					reader.Read(data, dataSize, sizeof(BYTE));
				}
				else { file->SeekCurrent(chunk.Size); }
			}

			return new WaveFile(fmt.ChannelNumber, fmt.SampleRate, fmt.ByteRate, fmt.BitsPerSample, data, dataSize);
		}

		AudioFormat WaveFile::GetFormat() const
		{
			if (m_ChannelNumber == 1)
			{
				if (m_BitsPerSample == 8) return AudioFormat::Mono8;
				else return AudioFormat::Mono16;
			}
			else
			{
				if (m_BitsPerSample == 8) return AudioFormat::Stereo8;
				else return AudioFormat::Stereo16;
			}
		}
	}
}