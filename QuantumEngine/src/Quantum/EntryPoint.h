#pragma once

#ifdef QT_PLATFORM_WINDOWS

extern Quantum::Application* Quantum::CreateApplication();

int main(int argc, char** argv) {
	Quantum::Log::Init();
	QT_CORE_WARN("init"); 
	auto app = Quantum::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif