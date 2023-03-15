#ifndef SQL_REQUESTS
#define SQL_REQUESTS

#include <QString>

inline QString select_user()
{
    return "SELECT * FROM User WHERE ID_User = :login AND Password = :password";
}

inline QString select_user_by_id()
{
    return "SELECT * FROM User WHERE ID_User = :id_user";
}

inline QString select_admin()
{
    return "SELECT * FROM User WHERE ID_User = :login AND Password = :password AND Code = :code";
}

inline QString select_all_users()
{
    return "SELECT * FROM User WHERE Role = :id_role AND ID_Group = :id_group";
}

inline QString insert_user()
{
    return "INSERT INTO User (ID_User, Fullname, ID_Group, Role, Password, Code) VALUES (:id_user, :fullname, :group, :role, :password, :code)";
}

inline QString edit_user()
{
    return "UPDATE User SET Fullname = :fullname, ID_Group = :group, Role = :role, Password = :password, Code = :code WHERE ID_User = :id_user";
}

inline QString select_theorypage_by_id()
{
    return "SELECT * FROM TheoryPage WHERE ID_Page = :id";
}

inline QString select_theorypage_by_name()
{
    return "SELECT * FROM TheoryPage WHERE Name_Theme = :name";
}

inline QString select_demopage()
{
    return "SELECT * FROM DemoPage WHERE Number_Page = :number AND ID_Type = :type";
}

inline QString select_question()
{
    return "SELECT * FROM Question WHERE ID_Question = :id_question AND ID_Theme = :id_theme";
}

#endif // SQL_REQUESTS

