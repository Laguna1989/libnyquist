#if defined(_MSC_VER)
#pragma comment(lib, "dsound.lib")
#endif

#include "AudioDevice.h"
#include "AudioDecoder.h"

#include <thread>

using namespace nqr;

int main()
{
	AudioDevice::ListAudioDevices();

    int desiredSampleRate = 44100;
	AudioDevice myDevice(2, desiredSampleRate);
	myDevice.Open(myDevice.info.id);
    
	AudioData * fileData = new AudioData();
    
    NyquistIO loader;
    
	try
	{
        
        //auto result = loader.Load(fileData, "test_data/1ch/44100/8/test.wav");
        //auto result = loader.Load(fileData, "test_data/1ch/44100/16/test.wav");
        //auto result = loader.Load(fileData, "test_data/1ch/44100/24/test.wav");
        //auto result = loader.Load(fileData, "test_data/1ch/44100/32/test.wav");
        //auto result = loader.Load(fileData, "test_data/1ch/44100/64/test.wav");
        
        //auto result = loader.Load(fileData, "test_data/2ch/44100/8/test.wav");
        //auto result = loader.Load(fileData, "test_data/2ch/44100/16/test.wav");
        //auto result = loader.Load(fileData, "test_data/2ch/44100/24/test.wav");
        auto result = loader.Load(fileData, "test_data/2ch/44100/32/test.wav");
        //auto result = loader.Load(fileData, "test_data/2ch/44100/64/test.wav");
        
        //auto result = loader.Load(fileData, "test_data/ad_hoc/6_channel_44k_16b.wav");
        
        //auto result = loader.Load(fileData, "test_data/ad_hoc/LR_Stereo.ogg");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/TestLaugh_44k.ogg");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/TestBeat.ogg");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/TestBeatMono.ogg");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/BlockWoosh_Stereo.ogg");
        
        //auto result = loader.Load(fileData, "test_data/ad_hoc/KittyPurr8_Stereo_Dithered.flac");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/KittyPurr16_Stereo.flac");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/KittyPurr16_Mono.flac");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/KittyPurr24_Stereo.flac");
        
        //auto result = loader.Load(fileData, "test_data/ad_hoc/detodos.opus"); // "Firefox: From All, To All"
        
        //auto result = loader.Load(fileData, "test_data/ad_hoc/TestBeat_Float32.wv");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/TestBeat_Float32_Mono.wv");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/TestBeat_Int16.wv");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/TestBeat_Int24.wv");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/TestBeat_Int32.wv");
        //auto result = loader.Load(fileData, "test_data/ad_hoc/TestBeat_Int24_Mono.wv");
        
        std::cout << "[Debug] Loader Status: " << result << std::endl;
	}
	catch (std::exception e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
        std::exit(1);
	}

    // Libnyquist does not do sample rate conversion
    if (fileData->sampleRate != desiredSampleRate)
    {
        std::cout << "[Warning - Sample Rate Mismatch] - file is sampled at " << fileData->sampleRate << " and output is " << desiredSampleRate << std::endl;
    }
    
    // Convert mono to stereo for testing playback
    if (fileData->channelCount == 1)
    {
        std::vector<float> stereoCopy(fileData->samples.size() * 2);
        
        int m = 0;
        for (size_t i = 0; i < stereoCopy.size(); i+=2)
        {
            stereoCopy[i] = fileData->samples[m];
            stereoCopy[i+1] = fileData->samples[m];
            m++;
        }
        myDevice.Play(stereoCopy);
    }
    else
    {
        std::cout << "Playing for: " << fileData->lengthSeconds << " seconds..." << std::endl;
      	myDevice.Play(fileData->samples);
    }

	return 0;
}