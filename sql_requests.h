#ifndef SQL_REQUESTS
#define SQL_REQUESTS

#include <QString>

/*
 *  Rus:
 *      Область запросов с пользователями
*/
inline QString select_user()
{
    return "SELECT * FROM User WHERE ID_User = :login AND Password = :password AND Status = :id_status";
}

inline QString select_user_by_id()
{
    return "SELECT * FROM User WHERE ID_User = :id_user";
}

inline QString select_admin()
{
    return "SELECT * FROM User WHERE ID_User = :login AND Password = :password AND Code = :code AND Status = :id_status";
}

inline QString select_status_user_by_id()
{
    return "SELECT Status FROM User WHERE ID_User = :id_user";
}

inline QString select_all_users_with_selections()
{
    return "SELECT * FROM User WHERE Role = :id_role AND ID_Group = :id_group AND Status = :id_status";
}

inline QString select_all_users()
{
    return "SELECT * FROM User";
}

inline QString insert_user()
{
    return "INSERT INTO User (ID_User, Fullname, ID_Group, Role, Password, Code, Status) VALUES (:id_user, :fullname, :group, :role, :password, :code, 1)";
}

inline QString edit_user()
{
    return "UPDATE User SET Fullname = :fullname, ID_Group = :group, Role = :role, Password = :password, Code = :code WHERE ID_User = :id_user";
}

inline QString mark_unmark_for_delete()
{
    return "UPDATE User SET Status = :id_status WHERE ID_User = :id_user";
}
// -- конец области --


// -------------------------------------------------------
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

inline QString select_number_of_questions()
{
    return "SELECT NumberOfQuestions FROM ThemeTest WHERE ID_Theme = :id_theme";
}

inline QString select_name_test()
{
    return "SELECT Name FROM ThemeTest WHERE ID_Theme = :id_theme";
}

inline QString select_question()
{
    return "SELECT * FROM Question WHERE ID_Question = :id_question AND ID_Theme = :id_theme";
}

inline QString insert_test_result()
{
    return "INSERT INTO ResultTest (ID_User, ID_Theme, Grade, Date) VALUES (:id_user, :id_theme, :grade, :date)";
}

inline QString select_test_results_for_user()
{
    return "SELECT * FROM ResultTest WHERE ID_User = :id_user";
}

#endif // SQL_REQUESTS

