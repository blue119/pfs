#include "pfs/parsers.hpp"
#include "pfs/utils.hpp"
#include <iostream>
#include <regex>


namespace pfs {
namespace impl {
namespace parsers {

limit parse_limit_line(const std::string& line)
{
   //Limit                     Soft Limit           Hard Limit           Units
   //Max cpu time              unlimited            unlimited            seconds
   //Max file size             unlimited            unlimited            bytes
   //Max data size             unlimited            unlimited            bytes
   //Max stack size            8388608              unlimited            bytes
   //Max core file size        0                    unlimited            bytes
   //Max resident set          unlimited            unlimited            bytes
   //Max processes             62812                62812                processes
   //Max open files            1024                 4096                 files
   //Max locked memory         8388608              8388608              bytes
   //Max address space         unlimited            unlimited            bytes
   //Max file locks            unlimited            unlimited            locks
   //Max pending signals       62812                62812                signals
   //Max msgqueue size         819200               819200               bytes
   //Max nice priority         0                    0
   //Max realtime priority     0                    0
   //Max realtime timeout      unlimited            unlimited            us

    // enum token
    // {
        // HIERARCHY   = 0,
        // CONTROLLERS = 1,
        // PATHNAME    = 2,
        // COUNT
    // };

    // static const char DELIM             = ' ';
    // static const char CONTROLLERS_DELIM = ',';

    // auto tokens = utils::split(line, DELIM, /* keep_empty = */ false);
    //std::regex limit_expr ("(^Max [a-z]+|[ ]{1})( {2,}).*");
    //std::smatch sm;
    //std::regex_match (line, sm, limit_expr);
    //std::regex_match ( line.cbegin(), line.cend(), sm, limit_expr);
    //std::cout << "String:range, size:" << sm.size() << " matches\n";
    //if (sm.size() == 0) {
    //    std::cout << line << '\n';
    //}
    //for (size_t i = 0; i < sm.size(); ++i) {
    //    std::cout << sm[i] << '\n';
    //}
    //    std::cout << '\n';





    // auto tokens = utils::split(line);
    // std::cout << tokens.size() << '\n';
    // for (auto i : tokens) {
        // std::cout << i << '\n';
    // }


    //if (tokens.size() != COUNT)
    //{
    //    throw parser_error("Corrupted cgroup line - Unexpected tokens count",
    //                       line);
    //}

    std::regex rgx("\\s{2,}");
    std::sregex_token_iterator iter(line.begin(), line.end(), rgx, -1);
    std::sregex_token_iterator end;
    // for ( ; iter != end; ++iter)
        // std::cout << *iter << '\n';

    try
    {
        limit lt;
        lt.name = *iter++;
        lt.soft = *iter++;
        lt.hard = *iter++;
        if (iter != end) {
            lt.unit = *iter++;
        }


        // std::cout << lt.name << '-' << lt.soft << '-' << lt.hard<< '-' << lt.unit<< '\n' << '\n';
        // utils::stot(tokens[HIERARCHY], cg.hierarchy);

        // cg.controllers = utils::split(tokens[CONTROLLERS], CONTROLLERS_DELIM);

        // cg.pathname = tokens[PATHNAME];

        return lt;
    }
    catch (const std::invalid_argument& ex)
    {
        throw parser_error("Corrupted limit - Invalid argument", line);
    }
    catch (const std::out_of_range& ex)
    {
        throw parser_error("Corrupted limit - Out of range", line);
    }
}

} // namespace parsers
} // namespace impl
} // namespace pfs

