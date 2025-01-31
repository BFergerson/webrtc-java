/*
 * Copyright 2019 Alex Andres
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "media/video/desktop/DesktopCapturer.h"

#include "modules/desktop_capture/desktop_capturer.h"
#include "modules/desktop_capture/desktop_capture_options.h"

namespace jni
{
	DesktopCapturer::DesktopCapturer(bool screenCapturer)
	{
		auto options = webrtc::DesktopCaptureOptions::CreateDefault();
		// Disable desktop effects.
		options.set_disable_effects(false);

#if defined(WEBRTC_WIN)
		options.set_allow_directx_capturer(true);
		options.set_allow_use_magnification_api(true);
#endif

		if (screenCapturer) {
			capturer = webrtc::DesktopCapturer::CreateScreenCapturer(options);
		}
		else {
			capturer = webrtc::DesktopCapturer::CreateWindowCapturer(options);
		}
	}

	DesktopCapturer::~DesktopCapturer()
	{
		capturer.reset();
	}

	void DesktopCapturer::Start(Callback * callback)
	{
		capturer->Start(callback);
	}

	void DesktopCapturer::SetSharedMemoryFactory(std::unique_ptr<webrtc::SharedMemoryFactory> factory)
	{
		capturer->SetSharedMemoryFactory(std::move(factory));
	}

	void DesktopCapturer::CaptureFrame()
	{
		capturer->CaptureFrame();
	}

	void DesktopCapturer::SetExcludedWindow(webrtc::WindowId window)
	{
		capturer->SetExcludedWindow(window);
	}

	bool DesktopCapturer::GetSourceList(SourceList * sources)
	{
		return capturer->GetSourceList(sources);
	}

	bool DesktopCapturer::SelectSource(SourceId id)
	{
		return capturer->SelectSource(id);
	}

	bool DesktopCapturer::FocusOnSelectedSource()
	{
		return capturer->FocusOnSelectedSource();
	}

	bool DesktopCapturer::IsOccluded(const webrtc::DesktopVector & pos)
	{
		return capturer->IsOccluded(pos);
	}
}