#include "Misc/AutomationTest.h"
#include "OpenAICompatibleComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FOpenAIConfigPreset, "FANTASIA.OpenAICompatible.Preset.OpenAI",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FOpenAIConfigPreset::RunTest(const FString& Parameters)
{
	FOpenAICompatibleConfig C = UOpenAICompatibleComponent::MakeOpenAIConfig();
	TestEqual(TEXT("URL"), C.URL, FString(TEXT("https://api.openai.com/v1/chat/completions")));
	TestEqual(TEXT("Model"), C.DefaultModel, FString(TEXT("gpt-4-turbo-preview")));
	TestEqual(TEXT("Timeout"), C.TimeoutSeconds, 60);
	TestTrue(TEXT("Auth"), C.bRequiresAuth);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGroqConfigPreset, "FANTASIA.OpenAICompatible.Preset.Groq",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGroqConfigPreset::RunTest(const FString& Parameters)
{
	FOpenAICompatibleConfig C = UOpenAICompatibleComponent::MakeGroqConfig();
	TestEqual(TEXT("URL"), C.URL, FString(TEXT("https://api.groq.com/openai/v1/chat/completions")));
	TestEqual(TEXT("Model"), C.DefaultModel, FString(TEXT("llama3-8b-8192")));
	TestEqual(TEXT("Timeout"), C.TimeoutSeconds, 30);
	TestTrue(TEXT("Auth"), C.bRequiresAuth);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FOllamaConfigPreset, "FANTASIA.OpenAICompatible.Preset.Ollama",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FOllamaConfigPreset::RunTest(const FString& Parameters)
{
	FOpenAICompatibleConfig C = UOpenAICompatibleComponent::MakeOllamaConfig();
	TestEqual(TEXT("URL"), C.URL, FString(TEXT("http://localhost:11434/v1/chat/completions")));
	TestEqual(TEXT("Model"), C.DefaultModel, FString(TEXT("llama3")));
	TestEqual(TEXT("Timeout"), C.TimeoutSeconds, 120);
	TestFalse(TEXT("No auth"), C.bRequiresAuth);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLMStudioConfigPreset, "FANTASIA.OpenAICompatible.Preset.LMStudio",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FLMStudioConfigPreset::RunTest(const FString& Parameters)
{
	FOpenAICompatibleConfig C = UOpenAICompatibleComponent::MakeLMStudioConfig();
	TestEqual(TEXT("URL"), C.URL, FString(TEXT("http://localhost:1234/v1/chat/completions")));
	TestEqual(TEXT("Model"), C.DefaultModel, FString(TEXT("local-model")));
	TestEqual(TEXT("Timeout"), C.TimeoutSeconds, 120);
	TestFalse(TEXT("No auth"), C.bRequiresAuth);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVLLMConfigPreset, "FANTASIA.OpenAICompatible.Preset.vLLM",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FVLLMConfigPreset::RunTest(const FString& Parameters)
{
	FOpenAICompatibleConfig C = UOpenAICompatibleComponent::MakeVLLMConfig();
	TestEqual(TEXT("URL"), C.URL, FString(TEXT("http://localhost:8000/v1/chat/completions")));
	TestEqual(TEXT("Model"), C.DefaultModel, FString(TEXT("default")));
	TestEqual(TEXT("Timeout"), C.TimeoutSeconds, 120);
	TestFalse(TEXT("No auth"), C.bRequiresAuth);
	return true;
}
