#include "StdAfx.h"
#include "Project.h"


#if 0
void extract_source_files_from_visual_studio_project( const std::string& vcproj_path, std::vector<std::string>& source_files )
{
    source_files.clear();

    std::string s = Utility::get_string_from_file( vcproj_path );

    static const std::string& configuration_type = Configuration::instance().get_configuration( CONFIG_SECTION_PROJECT_SETTING, CONFIG_KEY_CONFIGURATION_TYPE );

    if ( s.empty() )
    {
        FUNCTION_EXIT;
        return;
    }

    {
        // extract files
        static const boost::regex file_regex
            (
            "(?x)"
            "<File \\s+"
            "RelativePath=\" ( [^\"]+ ) \"  "   //$1, file relative path
            " .*? > "
            " \\s* ( .*? ) \\s* "               //$2, configurations
            "</File>"
            );

        static const boost::regex file_configuration_regex
            (
            "(?x)"
            "<FileConfiguration \\s+"
            "Name= \" ( .+? )  \" \\s+"                 //$1, Name
            "ExcludedFromBuild= \" ( .+? ) \" \\s+ "    //$2, ExcludedFromBuild
            ">"
            );

        boost::sregex_iterator it( s.begin(), s.end(), file_regex );
        boost::sregex_iterator end;

        for ( ; it != end; ++it )
        {
            std::string source_file_relative_path = it->str(1);
            std::string configurations = it->str(2);

            boost::trim( source_file_relative_path );

            if ( false == Utility::is_source_file( source_file_relative_path ) )
            {
                continue;
            }

            bool is_excluded = false;

            if ( false == configurations.empty() )
            {
                boost::sregex_iterator fc_it( configurations.begin(), configurations.end(), file_configuration_regex );
                boost::sregex_iterator end;

                for ( ; fc_it != end; ++fc_it )
                {
                    std::string file_configuration_name = fc_it->str(1);
                    std::string excluded_form_build = fc_it->str(2);

                    std::stringstream match_strm;
                    match_strm << configuration_type << "|Win32";

                    if ( file_configuration_name == match_strm.str() )
                    {
                        if ( "true" == excluded_form_build )
                        {
                            is_excluded = true;
                        }

                        break;
                    }
                }
            }

            if ( false == is_excluded )
            {
                boost::replace_all( source_file_relative_path, "\\", "/" );

                if ( boost::starts_with( source_file_relative_path, "./" ) )
                {
                    source_files.push_back( source_file_relative_path.substr( 2, std::string::npos ) );
                }
                else
                {
                    source_files.push_back( source_file_relative_path );
                }
            }
        }
    }
}
#endif
