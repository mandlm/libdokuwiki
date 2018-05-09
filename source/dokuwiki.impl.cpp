#include "dokuwiki.impl.h"

#include <iostream>

template <>
xmlrpc_c::value DokuWiki::impl::executeCommand(const std::string &command,
	const std::list<std::string> &params,
	const std::map<std::string, xmlrpc_c::value> &attributes)
{
	xmlrpc_c::client_xml client(&m_clientTransport);

	xmlrpc_c::paramList requestParams;
	for (const auto &param : params)
	{
		requestParams.add(xmlrpc_c::value_string(param));
	}

	if (!attributes.empty())
	{
		requestParams.add(xmlrpc_c::value_struct(attributes));
	}

	xmlrpc_c::rpcPtr rpc(command, requestParams);

	xmlrpc_c::carriageParm_curl0 carriageParm(m_url);

	rpc->call(&client, &carriageParm);

	return rpc->getResult();
}

template <>
xmlrpc_c::value_struct DokuWiki::impl::executeCommand(
	const std::string &command, const std::list<std::string> &params,
	const std::map<std::string, xmlrpc_c::value> &attributes)
{
	try
	{
		return xmlrpc_c::value_struct(
			executeCommand<xmlrpc_c::value>(command, params, attributes));
	}
	catch (girerr::error &e)
	{
		throw DokuWiki::error(e.what());
	}
}

template <>
std::string DokuWiki::impl::executeCommand(const std::string &command,
	const std::list<std::string> &params,
	const std::map<std::string, xmlrpc_c::value> &attributes)
{
	try
	{
		return xmlrpc_c::value_string(
			executeCommand<xmlrpc_c::value>(command, params, attributes));
	}
	catch (girerr::error &e)
	{
		throw DokuWiki::error(e.what());
	}
}

template <>
int DokuWiki::impl::executeCommand(const std::string &command,
	const std::list<std::string> &params,
	const std::map<std::string, xmlrpc_c::value> &attributes)
{
	try
	{
		return xmlrpc_c::value_int(
			executeCommand<xmlrpc_c::value>(command, params, attributes));
	}
	catch (girerr::error &e)
	{
		throw DokuWiki::error(e.what());
	}
}

template <>
bool DokuWiki::impl::executeCommand(const std::string &command,
	const std::list<std::string> &params,
	const std::map<std::string, xmlrpc_c::value> &attributes)
{
	try
	{
		return xmlrpc_c::value_boolean(
			executeCommand<xmlrpc_c::value>(command, params, attributes));
	}
	catch (girerr::error &e)
	{
		throw DokuWiki::error(e.what());
	}
}

DokuWiki::impl::impl(const std::string &url, const std::string &username,
	const std::string &password)
	: m_url(url)
{
	login(username, password);
}

void DokuWiki::impl::login(
	const std::string &username, const std::string &password)
{
	if (executeCommand<bool>("dokuwiki.login", {username, password}) == false)
	{
		throw DokuWiki::error("login failed");
	}
}

std::string DokuWiki::impl::getVersion()
{
	return executeCommand<std::string>("dokuwiki.getVersion");
}

std::string DokuWiki::impl::getTime()
{
	std::time_t currentTime = executeCommand<int>("dokuwiki.getTime");

	return std::asctime(std::localtime(&currentTime));
}

std::string DokuWiki::impl::getPage(const std::string &pageName)
{
	return executeCommand<std::string>("wiki.getPage", {pageName});
}

std::string DokuWiki::impl::getWikiTitle()
{
	return executeCommand<std::string>("dokuwiki.getTitle");
}

DokuWiki::PageInfo DokuWiki::impl::getPageInfo(const std::string &pageName)
{
	auto values = static_cast<std::map<std::string, xmlrpc_c::value>>(
		executeCommand<xmlrpc_c::value_struct>("wiki.getPageInfo", {pageName}));

	std::time_t modificationTime = xmlrpc_c::value_int(values["version"]);

	DokuWiki::PageInfo pageInfo = {xmlrpc_c::value_string(values["name"]),
		xmlrpc_c::value_string(values["author"]),
		std::asctime(std::localtime(&modificationTime))};

	return pageInfo;
}

bool DokuWiki::impl::pageExists(const std::string &pageName)
{
	try
	{
		getPageInfo(pageName);
		return true;
	}
	catch (std::runtime_error &)
	{
		return false;
	}
}

void DokuWiki::impl::putPage(
	const std::string &pageName, const std::string &content)
{
	if (!executeCommand<bool>("wiki.putPage", {pageName, content},
			{{"sum", xmlrpc_c::value_string("Added automatically")},
				{"minor", xmlrpc_c::value_boolean(false)}}))
	{
		throw std::runtime_error("failed to add page");
	}
}

void DokuWiki::impl::addPage(
	const std::string &pageName, const std::string &content)
{
	if (pageExists(pageName))
	{
		throw std::runtime_error("page already exists");
	}

	putPage(pageName, content);
}

void DokuWiki::impl::appendToPage(
	const std::string &pageName, const std::string &content)
{
	if (!executeCommand<bool>("dokuwiki.appendPage", {pageName, content},
			{{"sum", xmlrpc_c::value_string("Added automatically")},
				{"minor", xmlrpc_c::value_boolean(false)}}))
	{
		throw std::runtime_error("failed to append to page");
	}
}
