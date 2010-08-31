#include "MOFCCommandLine.hh"
#include "ContentsVisitor.hh"

#include <algorithm>
#include <iostream>

int main(int argc, char * argv[])
{
    MOFCCommandLine::get_instance()->run(argc, argv, "mofc", "MOFC_OPTIONS", "MOFC_CMDLINE");
    std::shared_ptr<paludis::Environment> env(paludis::EnvironmentFactory::get_instance()->create(MOFCCommandLine::get_instance()->a_environment.argument()));
    std::shared_ptr<paludis::PackageIDSequence> ids = (*env)[paludis::selection::AllVersionsSorted(paludis::generator::InRepository(paludis::RepositoryName("installed")))];
    ContentsList contents;
    bool multiOwnersFound = false;
    for(paludis::PackageIDSequence::ConstIterator pkgID(ids->begin()), pkgID_end(ids->end()); pkgID != pkgID_end; ++pkgID)
    {
		if((*pkgID)->contents_key().get() != NULL)
		{
			ContentsVisitor visitor(*pkgID, &contents);
			std::for_each(
				paludis::indirect_iterator((*pkgID)->contents_key()->value()->begin()),
				paludis::indirect_iterator((*pkgID)->contents_key()->value()->end()),
				paludis::accept_visitor(visitor)
			);
		}

    }
    for(ContentsList::const_iterator clit = contents.begin(), clit_end = contents.end(); clit != clit_end; ++clit)
    {
    	if(clit->second.size() > 1)
    	{
    		multiOwnersFound = true;
			std::cout << clit->first << std::endl;
			for(std::vector<std::shared_ptr<const paludis::PackageID> >::const_iterator pkgit = clit->second.begin(), pkgit_end = clit->second.end(); pkgit != pkgit_end; ++pkgit)
			{
				std::cout << "	" << (*pkgit)->canonical_form(paludis::idcf_full) << std::endl;
			}
    	}
    }
    if(!multiOwnersFound)
    {
    	std::cout << "No files owned by several packages found." << std::endl;
    }
	return EXIT_SUCCESS;
}
