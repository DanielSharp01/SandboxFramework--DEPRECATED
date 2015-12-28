#pragma once

#include <string>

#include "../IO/StreamReader.h"
#include "../IO/FileStream.h"
#include "AudioFormat.h"
typedef unsigned char BYTE;

namespace Sand
{
	namespace Audio
	{
		struct RIFF
		{
			char ChunkID[4];
			int ChunkSize;
			char Format[4];
		};

		struct WaveSubChunk
		{
			char ID[4];
			int Size;
		};

		struct WaveFMT : WaveSubChunk
		{
			short AudioFormat;
			short ChannelNumber;
			int SampleRate;
			int ByteRate;
			short BlockAlign;
			short BitsPerSample;
		};

		class WaveFile
		{
		private:
			short m_ChannelNumber;
			int m_SampleRate;
			int m_ByteRate;
			short m_BitsPerSample;

			BYTE* m_Data;
			int m_DataSize;

		public:
			WaveFile(short channelNumber, int sampleRate, int byteRate, short bitsPerSample, BYTE* data, int dataSize);
			~WaveFile();

			static WaveFile* Load(std::string path);

			inline short GetChannelNumber() const { return m_ChannelNumber; }
			inline int GetSampleRate() const { return m_SampleRate; }
			inline int GetByteRate() const { return m_ByteRate; }
			inline int GetBitsPerSample() const { return m_BitsPerSample; }
			inline BYTE* GetData() const { return m_Data; }
			inline int GetDataSize() const { return m_DataSize; }
			AudioFormat GetFormat() const;
		};
	}
}