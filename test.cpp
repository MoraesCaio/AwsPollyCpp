/*
* Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#include <aws/core/Aws.h>
#include <aws/text-to-speech/TextToSpeechManager.h>
#include <iostream>

using namespace std;

static const char* ALLOCATION_TAG = "PollySample::Main";

void DriveProgram();
void SelectVoiceAndOutputSound(Aws::TextToSpeech::TextToSpeechManager& manager);

int main()
{
	Aws::SDKOptions options;
	Aws::InitAPI(options);
	DriveProgram();
	Aws::ShutdownAPI(options);
	return 0;
}

void DriveProgram()
{
	auto client = Aws::MakeShared<Aws::Polly::PollyClient>(ALLOCATION_TAG);
	Aws::TextToSpeech::TextToSpeechManager manager(client);
	SelectVoiceAndOutputSound(manager);
}

void SelectVoiceAndOutputSound(Aws::TextToSpeech::TextToSpeechManager& manager)
{
	/*VOICES*/
	cout << "Available voices are: " << endl;
	cout << "[0] Ricardo or [1] Vitória" << endl;
	cout << "Please select voice you would like me to render (number or voice)." << endl;

	Aws::String voice;
	getline(cin, voice);
	Aws::String voiceLower = voice;
	transform(voiceLower.begin(), voiceLower.end(), voiceLower.begin(), ::tolower);

	if(!voice.compare("0") || !voiceLower.compare("ricardo"))
	{
		cout << "Selected voice: Ricardo" << endl;
		manager.SetActiveVoice("Ricardo");
	}
	else if(!voice.compare("1") || !voiceLower.compare("vitória"))
	{
		cout << "Selected voice: Vitória" << endl;
		manager.SetActiveVoice("Vitória");
	}
	else
	{
		cout << "Voice not available." << endl;
		SelectVoiceAndOutputSound(manager);
		return;
	}

	/*OUTPUT TEXT*/
	Aws::TextToSpeech::SendTextCompletedHandler handler;

	cout << "What would you like me to say in PT-BR? (Quit: \'exit\'\n Change voice: \'voice\')" << endl;
	Aws::String line;
	while (getline(cin, line))
	{
		if (line == "exit")
		{
			return;
		}
		if (line == "voice")
		{
			SelectVoiceAndOutputSound(manager);
			return;
		} 

		manager.SendTextToOutputDevice(line.c_str(), handler);
		cout << "Anything else?" << endl;
	}
}