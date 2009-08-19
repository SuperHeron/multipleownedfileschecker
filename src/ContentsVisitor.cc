#include "ContentsVisitor.hh"

ContentsVisitor::ContentsVisitor(const std::tr1::shared_ptr<const paludis::PackageID>& pkgID, ContentsList* contents)
{
	this->pkgID = pkgID;
	this->contents = contents;
}

void ContentsVisitor::visit(const paludis::ContentsFileEntry & d)
{
	std::string fileName = paludis::stringify(d.location_key()->value());
	ContentsList::iterator clit = this->contents->find(fileName);
	if(clit == this->contents->end())
	{
		std::vector<std::tr1::shared_ptr<const paludis::PackageID> > vector;
		vector.push_back(this->pkgID);
		this->contents->insert(std::make_pair(fileName, vector));
	}
	else
		clit->second.push_back(this->pkgID);
}

void ContentsVisitor::visit(const paludis::ContentsDirEntry & d)
{
}

void ContentsVisitor::visit(const paludis::ContentsOtherEntry & d)
{
}

void ContentsVisitor::visit(const paludis::ContentsSymEntry & d)
{
	std::string fileName = paludis::stringify(d.location_key()->value());
	ContentsList::iterator clit = this->contents->find(fileName);
	if(clit == this->contents->end())
	{
		std::vector<std::tr1::shared_ptr<const paludis::PackageID> > vector;
		vector.push_back(this->pkgID);
		this->contents->insert(std::make_pair(fileName, vector));
	}
	else
		clit->second.push_back(this->pkgID);
}
