#include "GeneralTTSThread.h"

using namespace std;

GeneralTTSThread* GeneralTTSThread::Runnable = nullptr;


GeneralTTSThread::GeneralTTSThread(FString inSsml, FString inID, FString url, UAudio2FaceComponent* A2F) : StopTaskCounter(0)
{
	ssml = inSsml;
	id = inID;
	Thread = FRunnableThread::Create(this, TEXT("GeneralTTSThread"), 0, TPri_Normal);
	Endpoint = url;
	A2FPointer = A2F;
}

GeneralTTSThread::~GeneralTTSThread() {
	delete Thread;
	Thread = NULL;
}


GeneralTTSThread* GeneralTTSThread::setup(FString ssml, FString id, FString Endpoint, UAudio2FaceComponent* A2F)
{
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new GeneralTTSThread(ssml, id, Endpoint, A2F);
	}
	return Runnable;
}

bool GeneralTTSThread::Init()
{
	return true;
}

uint32 GeneralTTSThread::Run()
{
	SynthesizeStream();
	return 0;
}

void GeneralTTSThread::Stop()
{
	StopTaskCounter.Increment();
}

void GeneralTTSThread::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void GeneralTTSThread::Shutdown()
{
	if (Runnable)
	{
		Runnable = NULL;
	}
}

void GeneralTTSThread::Synthesize() {
	// questa funzione va modificata in modo tale che diventa uguale a Ollama Component, cioè deve osservare
	// se quest'ultima ha o meno la disponibilità di streaming, quindi guarda la e vedi se riesci a fare sta roba
	//devo risolvere sto problem

	


	//Http request to API
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if (bWasSuccessful && Response.IsValid())
			{
				TArray<uint8> ResponseData = Response->GetContent();

				FTTSData SyntResult;
				SyntResult.AudioData = ResponseData;
				SyntResult.ssml = ssml;


				TTSResultAvailable.Broadcast(SyntResult, id);

			}
			else
			{
				//Error Handling
				UE_LOG(LogTemp, Error, TEXT("Connection to the TTS endpoint failed."));
			}
		});
	Request->SetURL(Endpoint);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	Request->SetContentAsString(ssml);
	Request->ProcessRequest();

	//chiamo Audio2Face?

	//connetto a Audio2FaceComponent

}

void GeneralTTSThread::SynthesizeStream()
{

	UE_LOG(LogTemp, Log, TEXT("===> Avvio SynthesizeStream()"));

	//Streaming Handler
	PreviousBytes = 0;

	auto Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Endpoint);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	Request->SetHeader(TEXT("Accept"), TEXT("application/octet-stream"));
	//Request->SetContentAsString(ssml);

	// 2) Preparo i parametri "allTextIn" e "modello" in formato URL-encoded
	FString AllTextInValue = ssml;  // sostituisci col testo che vuoi mandare             // sostituisci con il modello che vuoi usare

	// URL-encode di ciascun valore (spazi -> +, caratteri speciali convertiti, ecc.)
	FString EncodedText = FGenericPlatformHttp::UrlEncode(AllTextInValue);

	// Costruisco la stringa del body come "allTextIn=Beh+che+dire&modello=LC"
	FString UrlEncodedBody = FString::Printf(
		TEXT("allTextIn=%s"),
		*EncodedText
	);

	Request->SetContentAsString(UrlEncodedBody);

	UE_LOG(LogTemp, Log, TEXT("===> URL: %s"), *Endpoint);
	UE_LOG(LogTemp, Log, TEXT("===> POST Body: %s"), *UrlEncodedBody);


	Request->OnRequestProgress64().BindLambda([this](FHttpRequestPtr Req, int64 BytesSent, int64 BytesReceived)
		{
			if (!Req.IsValid() || !Req->GetResponse().IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("Richiesta o risposta non valida durante lo streaming"));
				return;
			}
			UE_LOG(LogTemp, Warning, TEXT("Richiesta partita in Streaming"));

			const TArray<uint8>& FullData = Req->GetResponse()->GetContent();
			int64 newBytes = BytesReceived - PreviousBytes;
			if (newBytes > 0)
			{
				UE_LOG(LogTemp, Log, TEXT("===> Ricevuti %lld nuovi byte (totale %lld)"), newBytes, BytesReceived);

				const uint8* NewDataPtr = FullData.GetData() + PreviousBytes;

				//converto in float
				int32 NumSamples = newBytes / 2;

				TArray<float> FloatBuffer;
				FloatBuffer.Reserve(NumSamples);

				for (int32 i = 0; i < NumSamples; ++i)
				{
					// Lettura int16 little endian
					int16 Sample = *(reinterpret_cast<const int16*>(NewDataPtr + i * 2));

					// Converti in float tra -1.0 e 1.0
					float NormalizedSample = Sample / 32768.0f;

					FloatBuffer.Add(NormalizedSample);
				}

				//TODO finisci
				if (A2FPointer)
				{
					UE_LOG(LogTemp, Log, TEXT("===> Invio %d campioni audio a A2FPointer"), FloatBuffer.Num());
					UE_LOG(LogTemp, Log, TEXT("===> Invio %d bytes audio a A2FPointer"), FloatBuffer.Num() * 4);
					A2FPointer->PlayAudio(FloatBuffer);
				}

				PreviousBytes = BytesReceived;
				//Sleep(100);
			}
		});

	//OnProcessRequesComplete
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bSuccess)
		{
			if (!bSuccess)
			{
				UE_LOG(LogTemp, Error, TEXT("===> Richiesta fallita"));
				return;
			}

			if (!Resp.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("===> Risposta non valida"));
				return;
			}

			int32 StatusCode = Resp->GetResponseCode();
			UE_LOG(LogTemp, Log, TEXT("===> Richiesta completata con codice HTTP: %d"), StatusCode);

			if (StatusCode != 200)
			{
				UE_LOG(LogTemp, Warning, TEXT("===> Codice di risposta inatteso. Corpo: %s"), *Resp->GetContentAsString());
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("===> Completamento avvenuto con successo"));
			}
		});

	UE_LOG(LogTemp, Log, TEXT("===> Invio della richiesta TTS..."));

	Request->ProcessRequest();

}

void GeneralTTSThread::OnTTSPartialDataReceived(FHttpRequestPtr Request, int64 BytesSent, int64 BytesReceived)
{

}

FDelegateHandle GeneralTTSThread::TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate)
{
	return TTSResultAvailable.Add(UseDelegate);
}

void GeneralTTSThread::TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle)
{
	TTSResultAvailable.Remove(DelegateHandle);
}