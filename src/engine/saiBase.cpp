////////////////////////////////////////////
//////
//Simple First Person Shooter Demo
//////
//by Eugen Schäfer
//////
////////////////////////////////////////////

#include "saiBase.h"

std::vector<std::string> loadTextfile(std::string fname)
{
    //std::cout << "loading file " << fname << std::endl;
    std::vector<std::string> lines;
    SDL_RWops *io = SDL_RWFromFile(fname.c_str(),"r"); //using RWOPS (for a future android port)
    if(io != NULL)
    {
        int i = io->size(io);
        char buff[i];
        if(io->read(io,buff,sizeof(buff),1)>0)
        {
            std::string nm = buff;
            std::string::size_type lastPos = nm.find_first_not_of('\n',0);
            std::string::size_type pos = nm.find_first_of('\n',lastPos);
            while(std::string::npos != pos || std::string::npos != lastPos)
            {
                lines.push_back(nm.substr(lastPos,pos - lastPos));
                lastPos = nm.find_first_not_of('\n',pos);
                pos = nm.find_first_of('\n',lastPos);
            }
        }
        else
        {
            std::cout << "Error: couldn't read data from " << fname << std::endl;
        }
    }
    else
    {
        std::cout << "Error: couldn't load file " << fname << std::endl;
    }
    io->close(io);
    return lines;
}

std::vector<std::string> getFilesFromDir(std::string dirname)
{
    std::vector<std::string> names;
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(dirname.c_str())) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            std::string line(ent->d_name);
            if(line[0] != '.')
            {
                names.push_back(line);
            }
        }
        closedir(dir);
    }
    else
    {
        std::cout << "Error, could not open directory " << dirname << std::endl;
    }
    return names;
}

std::string getParam(std::string p_string)
{
    std::stringstream ss;
    for(unsigned int i=0;i<p_string.size();i++)
    {
        if(p_string[i] != ' ' && p_string[i] != '\n')
        {
            ss << p_string[i];
        }
        else
        {
            break;
        }
    }
    return ss.str();
}
