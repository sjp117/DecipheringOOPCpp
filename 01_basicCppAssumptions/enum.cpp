#include <iostream>

// traditional enumerated types
enum day
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

enum workDay
{
    Mon = 1,
    Tues,
    Wed,
    Thurs,
    Fri
};

// strongly typed enumerated types can be a struct or class
enum struct WinterHoliday
{
    Diwali,
    Hanukka,
    ThreeKings,
    WinterSolstice,
    StLucina,
    StNicholas,
    Christmas,
    Kwanzaa
};

enum class Holiday : short int
{
    NewYear = 1,
    MLK,
    Memorial,
    Independence,
    Labor,
    Thanksgiving
};

int main()
{
    day birthday = Monday;
    workDay payday = Fri;
    WinterHoliday myTradition = WinterHoliday::StNicholas;
    Holiday favorite = Holiday::NewYear;

    std::cout << "Birthday is " << birthday << std::endl;
    std::cout << "Payday is " << payday << std::endl;
    std::cout << "Traditional Winder holiday is " << static_cast<int>(myTradition) << std::endl;
    std::cout << "Favorite holiday is " << static_cast<short int>(favorite) << std::endl;

    return 0;
}