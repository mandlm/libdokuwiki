#pragma once

#include "dokuwiki.h"

#include <xmlrpc-c/client.hpp>

#include <string>
#include <list>

class DokuWiki::impl
{
	private:
		std::string m_url;
		xmlrpc_c::clientXmlTransport_curl m_clientTransport;

	public:
		impl(const std::string &url, const std::string &username, const std::string &password);

		void login(const std::string &username, const std::string &password);
		std::string getVersion();
		std::string getTime();
		std::string getPage(const std::string &pageName);
		std::string getWikiTitle();

		DokuWiki::PageInfo getPageInfo(const std::string &pageName);
	
		template <typename ReturnType>
		ReturnType executeCommand(const std::string &command, 
				const std::list<std::string> &params = {});
};

