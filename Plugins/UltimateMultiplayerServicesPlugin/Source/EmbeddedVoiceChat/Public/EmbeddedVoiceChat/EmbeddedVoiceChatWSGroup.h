/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Aug 2023
 */

#ifndef EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATWSGROUP_H
#define EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATWSGROUP_H

#include <memory>
#include <unordered_map>

#include "sio_client.h"

#include "EmbeddedVoiceChat_EXPORTS.h"
#include "EmbeddedVoiceChatCommon.h"
#include "EmbeddedVoiceChatChannel.h"

namespace EmbeddedVoiceChat {
	struct EMBEDDED_VOICE_CHAT_API WSChannel {
		std::shared_ptr<EmbeddedVoiceChat::Connection> connection;
		std::shared_ptr<EmbeddedVoiceChat::ConnectionHandler> connectionHandler;
		std::shared_ptr<EmbeddedVoiceChat::Channel> channel;
	};

	class EMBEDDED_VOICE_CHAT_API WSGroup : public std::enable_shared_from_this<WSGroup> {
	public:
		static std::shared_ptr<WSGroup> create();

		~WSGroup();

		/**
		* please call before join any group
		**/
		void connectWSServer(const std::string &wsServerURL, const std::map<std::string, std::string> &query,
		                     const std::map<std::string, std::string> &http_extra_headers);

		/**
		**/
		void disconnectWSServer();

		bool isWSServerConnected();

		/**
		* please call before join any group
		**/
		void setIceServers(const std::vector<std::string> &iceServers, int portRangeBegin, int portRangeEnd);

		// list all channels
		std::vector<std::shared_ptr<EmbeddedVoiceChat::Channel>> getChannels();

		/**
		* get number of player in a group
		**/
		void
		countGroup(const std::string &groupName = "Default", std::function<void(int const &)> const &count = nullptr);

		/**
		* join a group with the specified group name
		**/
		void joinGroup(const std::string &groupName = "Default");

		/**
		 * leave a group with the specified group name
		**/
		void leaveGroup(const std::string &groupName = "Default");

		/*
		 * internal use only.
		 * */
		void
		gotLocalDescription(const std::string &sessionId, const EmbeddedVoiceChat::DescriptionType &descriptionType,
		                    const std::string &description);

		/*
		 * internal use only.
		 * */
		void gotLocalCandidate(const std::string &sessionId, const std::string &mid, const std::string &candidate);

		/*
		 * internal use only.
		 * */
		void setChannel(const std::string &sessionId, std::shared_ptr<EmbeddedVoiceChat::Channel> channel);

	private:
		void newPlayerJoin(const std::string &sessionId);

		void oldPlayerLeave(const std::string &sessionId);

		/*
		 * internal use only.
		 * */
		void
		gotRemoteDescription(const std::string &sessionId, const EmbeddedVoiceChat::DescriptionType &descriptionType,
		                     const std::string &description);

		/*
		 * internal use only.
		 * */
		void gotRemoteCandidate(const std::string &sessionId, const std::string &mid, const std::string &candidate);

		sio::client *sioClient = nullptr;

		std::vector<std::string> iceServers;

		int portRangeBegin;

		int portRangeEnd;

		/*
		 * internal use only.
		 * socket id to connection / channel / connection handler / channel handler
		 * */
		std::unordered_map<std::string, EmbeddedVoiceChat::WSChannel> WSChannels;
	};

	class EMBEDDED_VOICE_CHAT_API WSGroup2 : public std::enable_shared_from_this<WSGroup2> {
	public:
		static std::shared_ptr<WSGroup2> create(const std::string &id);

		WSGroup2(const std::string &id = "");

		~WSGroup2();

		/**
	   * please call before join any group
	   **/
		void connectWSServer(const std::string &wsServerURL, const std::map<std::string, std::string> &query,
		                     const std::map<std::string, std::string> &http_extra_headers);

		 /**
		**/
		void disconnectWSServer();

		bool isWSServerConnected();

		 /**
		* please call before join any group
		**/
		void setIceServers(const std::vector<std::string> &iceServers, int portRangeBegin, int portRangeEnd);

		// get channel by id
		std::shared_ptr<EmbeddedVoiceChat::Channel> getChannel(const std::string &id = "");

		/**
		* get number of player in a group
		**/
		void
		countGroup(const std::string &groupName = "Default", std::function<void(int const &)> const &count = nullptr);

		/**
	   * join a group with the specified group name
	   **/
		void joinGroup(const std::string &groupName = "Default");

		 /**
		 * leave a group with the specified group name
		**/
		void leaveGroup(const std::string &groupName = "Default");

		 /*
		 * internal use only.
		 * */
		void
		gotLocalDescription(const std::string &sessionId, const EmbeddedVoiceChat::DescriptionType &descriptionType,
		                    const std::string &description);

		 /*
		 * internal use only.
		 * */
		void gotLocalCandidate(const std::string &sessionId, const std::string &mid, const std::string &candidate);

		 /*
		 * internal use only.
		 * */
		void setChannel(const std::string &sessionId, std::shared_ptr<EmbeddedVoiceChat::Channel> channel);

	private:
		void newPlayerJoin(const std::string &sessionId, const std::string &uId);

		void oldPlayerLeave(const std::string &sessionId, const std::string &uId);

		 /*
		 * internal use only.
		 * */
		void
		gotRemoteDescription(const std::string &sessionId, const std::string &uId, const EmbeddedVoiceChat::DescriptionType &descriptionType,
		                     const std::string &description);

		 /*
		 * internal use only.
		 * */
		void gotRemoteCandidate(const std::string &sessionId, const std::string &uId, const std::string &mid, const std::string &candidate);

		sio::client *sioClient = nullptr;

		std::vector<std::string> iceServers;

		int portRangeBegin;

		int portRangeEnd;

		std::string id;

		 /*
		 * internal use only.
		 * socket id to connection / channel / connection handler / channel handler
		 * */
		std::unordered_map<std::string, EmbeddedVoiceChat::WSChannel> WSChannels;

		 /*
		 * internal use only.
		 * id to socket id
		 * */
		std::unordered_map<std::string, std::string> players;
	};
	}

	extern

	"C" {
}


#endif //EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATWSGROUP_H
