#pragma once

#ifdef QT_PLATFORM_WINDOWS

extern Quantum::Application* Quantum::CreateApplication();

int main(int argc, char** argv) {
	Quantum::Log::Init();
	QT_CORE_WARN("init");
	int a = 5;
	QT_INFO("Init Var={0}", a);
	auto app = Quantum::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif