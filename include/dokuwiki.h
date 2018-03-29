#pragma once

#include <string>
#include <memory>

class DokuWiki
{
	public:
		using error = std::runtime_error;

		struct PageInfo
		{
			std::string name;
			std::string author;
			std::string timestamp;
		};

	public:
		DokuWiki(const std::string &url, const std::string &username, const std::string &password);
		~DokuWiki();

		std::string getVersion();
		std::string getTime();
		std::string getPage(const std::string &pageName);
		std::string getWikiTitle();
		PageInfo getPageInfo(const std::string &pageName);

	private:
		class impl;
		std::unique_ptr<impl> pimpl;
};

