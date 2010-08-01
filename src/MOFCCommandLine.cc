#include "MOFCCommandLine.hh"

#include <iostream>

template class paludis::Singleton<MOFCCommandLine>;

MOFCCommandLine::MOFCCommandLine() :
    ArgsHandler(),

    action_args(this->main_options_section(), "Actions", "Selects which basic action to perform. At most one action should be specified."),
    a_version(&action_args, "version", 'V',  "Display program version", false),
    a_help(&action_args, "help", 'h',  "Display program help", false),

    general_args(this->main_options_section(), "General options", "Options which are relevant for most or all actions."),
//    a_log_level(&general_args, "log-level", '\0'),
    a_environment(&general_args, "environment", 'E', "Environment specification (class:suffix, both parts optional)")
//    a_resume_command_template(&general_args, "resume-command-template", '\0', "Save the resume command to a file. If the filename contains 'XXXXXX', use mkstemp(3) to generate the filename")
{}

std::string MOFCCommandLine::app_name() const
{
    return "MultipleOwnedFilesChecker";
}

std::string MOFCCommandLine::app_synopsis() const
{
    return "Application to check which files are owned by multiple packages.";
}

std::string MOFCCommandLine::app_description() const
{
    return "This program will list files owned by several packages.";
}

MOFCCommandLine::~MOFCCommandLine()
{
}

void show_help_and_exit(const char * const argv[])
{
    std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
    std::cout << std::endl;
    std::cout << *MOFCCommandLine::get_instance();

    std::exit(EXIT_SUCCESS);
}

void show_version_and_exit()
{
    std::cout << "MultipleOwnedFilesChecker 1.0" << std::endl;

    std::exit(EXIT_SUCCESS);
}

void MOFCCommandLine::run(const int argc, const char * const * const argv, const std::string & client, const std::string & env_var, const std::string & env_prefix)
{
    paludis::args::ArgsHandler::run(argc, argv, client, env_var, env_prefix);

//    if (MOFCCommandLine::get_instance()->a_log_level.specified())
//        paludis::Log::get_instance()->set_log_level(MOFCCommandLine::get_instance()->a_log_level.option());

    if (MOFCCommandLine::get_instance()->a_help.specified())
        show_help_and_exit(argv);

    if (MOFCCommandLine::get_instance()->a_version.specified())
        show_version_and_exit();

}
