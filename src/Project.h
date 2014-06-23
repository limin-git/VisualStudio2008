#pragma once


struct Platform
{
    std::string m_name;
};

typedef std::vector<Platform> Platforms;


struct Tool
{
    std::string m_name;
    std::map<std::string, std::string> m_name_value_map;
};


struct Configuration
{
    std::string m_name;
    std::string m_output_directory;
    std::string m_intermediate_directory;
    std::string m_configuration_type;
    std::string m_character_set;

    Tool m_pre_build_event_tool;
    Tool m_custom_build_tool;
    Tool m_xml_data_generator_tool;
    Tool m_web_service_proxy_generator_tool;
    Tool m_midl_tool;
    Tool m_cl_compiler_tool;
    Tool m_managed_resource_compiler_tool;
    Tool m_resource_compiler_tool;
    Tool m_pre_link_event_tool;
    Tool m_linker_tool;
    Tool m_al_link_tool;
    Tool m_mainifest_tool;
    Tool m_xdc_make_tool;
    Tool m_bsc_make_tool;
    Tool m_cfx_cop_tool;
    Tool m_app_verfier_tool;
    Tool m_post_build_event_tool;
};

typedef std::vector<Configuration> Configurations;


struct IFile {};


struct FileConfiguration
{
    FileConfiguration() : m_tool(NULL) {}
    std::string m_name;
    std::string m_excluded_from_build;
    Tool* m_tool;
};


struct File : IFile
{
    File() : m_file_configuration(NULL) {}
    std::string m_relative_path;
    FileConfiguration* m_file_configuration;
};


struct Filter : IFile
{
    std::string m_name;
    std::vector<IFile*> m_children;
};

typedef std::vector<IFile*> Files;


struct Project
{
    Project( const std::string& path );

    std::vector<std::string> get_files( const std::string& configuration = "Debug|Win32" );

private:

    std::string m_path;

    std::string m_project_type;
    std::string m_version;
    std::string m_name;
    std::string m_project_guid;
    std::string m_root_namespace;
    std::string m_keyword;
    std::string m_target_framework_version;

    Platforms m_platforms;
    Configurations m_configurations;
    Files m_files;
};
