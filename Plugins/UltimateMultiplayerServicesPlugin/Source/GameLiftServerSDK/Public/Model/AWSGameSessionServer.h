/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, December 2018
 */

#pragma once

#include "CoreMinimal.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

#if WITH_GAMELIFT

#include "aws/gamelift/server/model/GameSession.h"

#endif

#include "Model/AWSGameSessionStatusServer.h"
#include "Model/GamePropertyServer.h"

#include "AWSGameSessionServer.generated.h"

UENUM(BlueprintType)
enum class EAWSGameLiftServerSDKMatchmakerDataAttributeType : uint8 {
	NOT_SET        UMETA(DisplayName = "not set"),
	STRING        UMETA(DisplayName = "string"),
	DOUBLE        UMETA(DisplayName = "double"),
	STRING_LIST        UMETA(DisplayName = "string list"),
	STRING_DOUBLE_MAP        UMETA(DisplayName = "string double map")
};

USTRUCT(BlueprintType)
struct FAWSGameLiftServerSDKMatchmakerDataAttributeValue {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
	EAWSGameLiftServerSDKMatchmakerDataAttributeType type = EAWSGameLiftServerSDKMatchmakerDataAttributeType::NOT_SET;

	/**
	*  <p>For single string values. Maximum string length is 100 characters.</p>
	**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
	FString s;

	/**
	*  <p>For number values, expressed as double.</p>
	**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
	float n = 0.0f;

	/**
	*  <p>For a list of up to 10 strings. Maximum length for each string is 100 characters. Duplicate values are not recognized; all occurrences of the repeated value after the first of a repeated value are ignored.</p>
	**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
	TArray<FString> sL;

	/**
	*  <p>For a map of up to 10 data type:value pairs. Maximum length for each string value is 100 characters. </p>
	**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLift Client")
	TMap<FString, float> sDM;

#if WITH_GAMELIFT
public:
    FAWSGameLiftServerSDKMatchmakerDataAttributeValue& fromAWS(const TSharedPtr<FJsonObject> &attributeJsonObject) {
		s = "";
		n = 0.0f;
		sL.Empty();
		sDM.Empty();

		if (!attributeJsonObject) {
			return *this;
		}

		if (attributeJsonObject->HasTypedField<EJson::String>(FString("attributeType"))) {
			FString attributeType = attributeJsonObject->GetStringField(FString("attributeType"));

			if (attributeType.Equals(TEXT("NONE"), ESearchCase::IgnoreCase)) {
				type = EAWSGameLiftServerSDKMatchmakerDataAttributeType::NOT_SET;

				return *this;
			}

			if (attributeType.Equals(TEXT("STRING"), ESearchCase::IgnoreCase)) {
				type = EAWSGameLiftServerSDKMatchmakerDataAttributeType::STRING;

				if (attributeJsonObject->HasTypedField<EJson::String>(FString("valueAttribute"))) {
					s = attributeJsonObject->GetStringField(FString("valueAttribute"));
				}
			}

			if (attributeType.Equals(TEXT("DOUBLE"), ESearchCase::IgnoreCase)) {
				type = EAWSGameLiftServerSDKMatchmakerDataAttributeType::DOUBLE;

				if (attributeJsonObject->HasTypedField<EJson::Number>(FString("valueAttribute"))) {
					n = (float)attributeJsonObject->GetNumberField(FString("valueAttribute"));
				}
			}

			if (attributeType.Equals(TEXT("STRING_LIST"), ESearchCase::IgnoreCase)) {
				type = EAWSGameLiftServerSDKMatchmakerDataAttributeType::STRING_LIST;

				if (attributeJsonObject->HasTypedField<EJson::Array>(FString("valueAttribute"))) {
					TArray<TSharedPtr<FJsonValue>> valueAttributeJsonArray = attributeJsonObject->GetArrayField(FString("valueAttribute"));
					sL.Empty();
					for (const TSharedPtr<FJsonValue> &elem : valueAttributeJsonArray) {
						FString elemValue;
						if (elem->TryGetString(elemValue)) {
							sL.Add(elemValue);
						}
					}
				}
			}

			if (attributeType.Equals(TEXT("STRING_DOUBLE_MAP"), ESearchCase::IgnoreCase)) {
				type = EAWSGameLiftServerSDKMatchmakerDataAttributeType::STRING_DOUBLE_MAP;

				if (attributeJsonObject->HasTypedField<EJson::Object>(FString("valueAttribute"))) {
					TSharedPtr<FJsonObject> valueAttributeJsonObject = attributeJsonObject->GetObjectField(FString("valueAttribute"));

					sDM.Empty();
					for (const TPair<FString, TSharedPtr<FJsonValue>>& elem : valueAttributeJsonObject->Values) {
						float elemValue;
						if (elem.Value->TryGetNumber(elemValue)) {
							sDM.Add(elem.Key, elemValue);
						}
					}
				}
			}
		}

		return *this;
	}
#endif
};

USTRUCT(BlueprintType)
struct FAWSGameLiftServerSDKMatchmakerDataPlayer {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
	FString playerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
	TMap<FString, FAWSGameLiftServerSDKMatchmakerDataAttributeValue> attributes;

#if WITH_GAMELIFT
	public:
    FAWSGameLiftServerSDKMatchmakerDataPlayer& fromAWS(const TSharedPtr<FJsonObject> &playerJsonObject) {
		playerId = "";
		attributes.Empty();

		if (!playerJsonObject) {
			return *this;
		}

		if (playerJsonObject->HasTypedField<EJson::String>(FString("playerId"))) {
			playerId = playerJsonObject->GetStringField(FString("playerId"));
		}

		if (playerJsonObject->HasTypedField<EJson::Object>(FString("attributes"))) {
			TSharedPtr<FJsonObject> attributesJsonObject = playerJsonObject->GetObjectField(FString("attributes"));

			attributes.Empty();
			for (const TPair<FString, TSharedPtr<FJsonValue>>& elem : attributesJsonObject->Values) {
				TSharedPtr<FJsonObject> *attributeJsonObject = nullptr;
				if (elem.Value->TryGetObject(attributeJsonObject)) {
					attributes.Add(elem.Key, FAWSGameLiftServerSDKMatchmakerDataAttributeValue().fromAWS(*attributeJsonObject));
				}
			}
		}

        return *this;
    };

#endif
};

USTRUCT(BlueprintType)
struct FAWSGameLiftServerSDKMatchmakerDataTeam {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
	TArray<FAWSGameLiftServerSDKMatchmakerDataPlayer> players;

#if WITH_GAMELIFT
	public:
    FAWSGameLiftServerSDKMatchmakerDataTeam& fromAWS(const TSharedPtr<FJsonObject> &teamJsonObject) {
		name = "";
		players.Empty();

		if (!teamJsonObject) {
			return *this;
		}

		if (teamJsonObject->HasTypedField<EJson::String>(FString("name"))) {
			name = teamJsonObject->GetStringField(FString("name"));
		}

		if (teamJsonObject->HasTypedField<EJson::Array>(FString("players"))) {
			TArray<TSharedPtr<FJsonValue>> playersJsonArray = teamJsonObject->GetArrayField(FString("players"));
			players.Empty();
			for (const TSharedPtr<FJsonValue> &elem : playersJsonArray) {
				TSharedPtr<FJsonObject> *playerJsonObject = nullptr;
				if (elem->TryGetObject(playerJsonObject)) {
					players.Add(FAWSGameLiftServerSDKMatchmakerDataPlayer().fromAWS(*playerJsonObject));
				}
			}
		}

        return *this;
    };

#endif
};

USTRUCT(BlueprintType)
struct FAWSGameLiftServerSDKMatchmakerData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
	FString matchId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
	FString matchmakingConfigurationArn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
	TArray<FAWSGameLiftServerSDKMatchmakerDataTeam> teams;

#if WITH_GAMELIFT
	public:
    FAWSGameLiftServerSDKMatchmakerData& fromAWS(const std::string &awsMatchmakerData) {
		matchId = "";
		matchmakingConfigurationArn = "";
		teams.Empty();

		FString matchmakerData = FString(awsMatchmakerData.c_str());
		if (matchmakerData.IsEmpty()) {
			return *this;
		}

		TSharedPtr<FJsonObject> matchmakerDataJsonObject;
        TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(FString(awsMatchmakerData.c_str()));
        if (FJsonSerializer::Deserialize(Reader, matchmakerDataJsonObject)) {
			if (matchmakerDataJsonObject->HasTypedField<EJson::String>(FString("matchId"))) {
				matchId = matchmakerDataJsonObject->GetStringField(FString("matchId"));
			}

			if (matchmakerDataJsonObject->HasTypedField<EJson::String>(FString("matchmakingConfigurationArn"))) {
				matchmakingConfigurationArn = matchmakerDataJsonObject->GetStringField(FString("matchmakingConfigurationArn"));
			}

			if (matchmakerDataJsonObject->HasTypedField<EJson::Array>(FString("teams"))) {
				TArray<TSharedPtr<FJsonValue>> teamsJsonArray = matchmakerDataJsonObject->GetArrayField(FString("teams"));

				teams.Empty();
				for (const TSharedPtr<FJsonValue> &elem : teamsJsonArray) {
					TSharedPtr<FJsonObject> *teamJsonObject = nullptr;
					if (elem->TryGetObject(teamJsonObject)) {
						teams.Add(FAWSGameLiftServerSDKMatchmakerDataTeam().fromAWS(*teamJsonObject));
					}
				}
			}
        } else {
			// @TODO: error
		}

        return *this;
    };

#endif
};

USTRUCT(BlueprintType)
struct FAWSGameSessionServer {
    GENERATED_BODY()

    /**
    * <p>Unique identifier for a game session.</p>
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    FString gameSessionId;

    /**
    * <p>Descriptive label associated with a game session. Session names do not need
    * to be unique.</p>
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    FString name;

    /**
    * <p>Unique identifier for a fleet.</p>
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    FString fleetId;

    /**
    * <p>Maximum number of players allowed in the game session.</p>
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    int maximumPlayerSessionCount = 0;

    /**
    * <p>Current status of the game session. A game session must be in an
    * <code>ACTIVE</code> state to have player sessions.</p>
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    EGameSessionStatusServer status = EGameSessionStatusServer::NOT_SET;

    /**
     * <p>Set of custom property for the game session.</p>
     * don't add more than 32 elements
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    TArray<FGamePropertyServer> gameProperties;

    /**
    * <p>IP address of the game session. To connect to a GameLift server process, an
    * app needs both the IP address and port number.</p>
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    FString ipAddress;

    /**
    * <p>Port number for the game session. To connect to a GameLift server process, an
    * app needs both the IP address and port number.</p>
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    int port = 0;

    /**
    * <p>Custom data for the game session.</p>
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    FString gameSessionData;

    /**
    * <p>Data generated from GameLift Matchmaking.</p>
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    FString matchmakerData;

    /**
    * <p>Data generated from GameLift Matchmaking.</p>
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
	FAWSGameLiftServerSDKMatchmakerData matchmakerData_;

    /**
    * The DNS name of the host running a GameLift server process, used for establishing a TLS connection for a game session.
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Lift Server")
    FString dnsName;

#if WITH_GAMELIFT
    public:
    FAWSGameSessionServer& fromAWS(const Aws::GameLift::Server::Model::GameSession& awsGameSession) {
        this->gameSessionId = awsGameSession.GetGameSessionId();
        this->name = awsGameSession.GetName();
        this->fleetId = awsGameSession.GetFleetId();
        this->maximumPlayerSessionCount = awsGameSession.GetMaximumPlayerSessionCount();

        switch (awsGameSession.GetStatus()) {
            case Aws::GameLift::Server::Model::GameSessionStatus::NOT_SET:
                this->status = EGameSessionStatusServer::NOT_SET;
                break;
            case Aws::GameLift::Server::Model::GameSessionStatus::ACTIVE:
                this->status = EGameSessionStatusServer::ACTIVE;
                break;
            case Aws::GameLift::Server::Model::GameSessionStatus::ACTIVATING:
                this->status = EGameSessionStatusServer::ACTIVATING;
                break;
            case Aws::GameLift::Server::Model::GameSessionStatus::TERMINATED:
                this->status = EGameSessionStatusServer::TERMINATED;
                break;
            case Aws::GameLift::Server::Model::GameSessionStatus::TERMINATING:
                this->status = EGameSessionStatusServer::TERMINATING;
                break;
            default:
                break;
        }

        int count = 0;
        const Aws::GameLift::Server::Model::GameProperty* awsGameProperties = awsGameSession.GetGameProperties(count);
        this->gameProperties.Empty();
        for (int i = 0; i < count; i++) {
            this->gameProperties.Add(FGamePropertyServer().fromAWS(awsGameProperties[i]));
        }

        this->ipAddress = awsGameSession.GetIpAddress();
        this->port = awsGameSession.GetPort();
        this->gameSessionData = awsGameSession.GetGameSessionData();
        this->matchmakerData = awsGameSession.GetMatchmakerData();
        this->matchmakerData_.fromAWS(awsGameSession.GetMatchmakerData());
        this->dnsName = awsGameSession.GetDnsName();

        return *this;
    };

#endif
};