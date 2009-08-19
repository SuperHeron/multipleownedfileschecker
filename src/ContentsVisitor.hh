#ifndef __CONTENTS_VISITOR_HH__
#define __CONTENTS_VISITOR_HH__

#include <map>
#include <string>
#include <vector>

#include <paludis/paludis.hh>

typedef std::map<std::string, std::vector<std::tr1::shared_ptr<const paludis::PackageID> > > ContentsList;

class ContentsVisitor
{
    public:
        ContentsVisitor(const std::tr1::shared_ptr<const paludis::PackageID>&, ContentsList*);
        void visit(const paludis::ContentsFileEntry & d);
        void visit(const paludis::ContentsDirEntry & d);
        void visit(const paludis::ContentsOtherEntry & d);
        void visit(const paludis::ContentsSymEntry & d);
    private:
		std::tr1::shared_ptr<const paludis::PackageID> pkgID;
        ContentsList* contents;
};

#endif // __CONTENTS_VISITOR_HH__
