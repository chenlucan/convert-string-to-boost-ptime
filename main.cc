#include <iostream>
#include <boost/date_time.hpp>
namespace bt = boost::posix_time;
const std::locale formats[] = {
std::locale(std::locale::classic(),new bt::time_input_facet("%Y-%m-%d %H:%M:%S")),
std::locale(std::locale::classic(),new bt::time_input_facet("%Y/%m/%d %H:%M:%S")),
std::locale(std::locale::classic(),new bt::time_input_facet("%d.%m.%Y %H:%M:%S")),
std::locale(std::locale::classic(),new bt::time_input_facet("%Y-%m-%d"))};
const size_t formats_n = sizeof(formats)/sizeof(formats[0]);

std::time_t pt_to_time_t(const bt::ptime& pt)
{
    bt::ptime timet_start(boost::gregorian::date(1970,1,1));
    bt::time_duration diff = pt - timet_start;
    return diff.ticks()/bt::time_duration::rep_type::ticks_per_second;

}
void seconds_from_epoch(const std::string& s)
{
    bt::ptime pt;
    for(size_t i=0; i<formats_n; ++i)
    {
        std::istringstream is(s);
        is.imbue(formats[i]);
        is >> pt;
        if(pt != bt::ptime()) break;
    }
    std::cout << " ptime is " << pt << '\n';
    std::cout << " seconds from epoch are " << pt_to_time_t(pt) << '\n';
}
int main()
{
    seconds_from_epoch("2004-03-21 12:45:33");
    seconds_from_epoch("2004/03/21 12:45:33");
    seconds_from_epoch("23.09.2004 04:12:21");
    seconds_from_epoch("2003-02-11");
}
