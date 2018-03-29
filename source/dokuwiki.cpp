#include "dokuwiki.h"
#include "dokuwiki.impl.h"

#include <xmlrpc-c/client.hpp>

#include <iostream>

DokuWiki::DokuWiki(const std::string &url, const std::string &username, const std::string &password)
	: pimpl{std::make_unique<impl>(url, username, password)}
{
}

DokuWiki::~DokuWiki() = default;

std::string DokuWiki::getVersion()
{
	return pimpl->getVersion();
}

std::string DokuWiki::getTime()
{
	return pimpl->getTime();
}

std::string DokuWiki::getPage(const std::string &pageName)
{
	return pimpl->getPage(pageName);
}

std::string DokuWiki::getWikiTitle()
{
	return pimpl->getWikiTitle();
}

DokuWiki::PageInfo DokuWiki::getPageInfo(const std::string &pageName)
{
	return pimpl->getPageInfo(pageName);
}

bool DokuWiki::pageExists(const std::string &pageName)
{
	return pimpl->pageExists(pageName);
}

void DokuWiki::putPage(const std::string &pageName, const std::string &content)
{
	pimpl->putPage(pageName, content);
}

void DokuWiki::addPage(const std::string &pageName, const std::string &content)
{
	pimpl->addPage(pageName, content);
}

