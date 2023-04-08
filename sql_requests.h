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

inline QString select_group()
{
    return "SELECT Name_Group FROM 'Group' WHERE ID_Group = :id_group";
}

inline QString select_all_groups()
{
    return "SELECT * FROM 'Group'";
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
inline QString select_all_theory_pages()
{
    return "SELECT * FROM TheoryPage";
}

inline QString select_more_theory_pages()
{
    return "SELECT * FROM TheoryPage WHERE ID_Page > 14";
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

inline QString select_number_of_questions()
{
    return "SELECT NumberOfQuestions FROM ThemeTest WHERE ID_Theme = :id_theme";
}

inline QString select_name_test()
{
    return "SELECT Name FROM ThemeTest WHERE ID_Theme = :id_theme";
}

inline QString select_all_tests()
{
    return "SELECT * FROM ThemeTest";
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

inline QString select_theme_lab_work()
{
    return "SELECT * FROM ThemeWork WHERE ID_Theme = :id_theme";
}

inline QString select_all_themes_lab_works()
{
    return "SELECT * FROM ThemeWork";
}

inline QString select_all_statuses_works()
{
    return "SELECT * FROM WorkStatus";
}

inline QString select_id_status_work()
{
    return "SELECT Status FROM LabWork WHERE ID_User = :id_user AND ID_Work = :id_work";
}

inline QString select_status_work()
{
    return "SELECT (SELECT Name FROM WorkStatus WHERE ID_Status = Status) AS Status FROM LabWork WHERE ID_User = :id_user AND ID_Work = :id_work";
}

inline QString select_lab_work()
{
    return "SELECT * FROM LabWork WHERE ID_User = :id_user AND ID_Work = :id_work";
}

inline QString select_all_lab_works()
{
    return "SELECT 'Group'.Name_Group AS GroupName, User.ID_User, User.Fullname, "
           "TW.Name AS NameWork, WS.Name AS StatusWork FROM LabWork "
           "JOIN User ON LabWork.ID_User = User.ID_User "
           "JOIN 'Group' ON User.ID_Group = 'Group'.ID_Group "
           "JOIN ThemeWork TW on LabWork.ID_Work = TW.ID_Theme "
           "JOIN WorkStatus WS on LabWork.Status = WS.ID_Status";
}

inline QString select_all_lab_works_with_selections()
{
    return "SELECT 'Group'.Name_Group AS GroupName, User.ID_User, User.Fullname, "
           "TW.Name AS NameWork, WS.Name AS StatusWork FROM LabWork "
           "JOIN User ON LabWork.ID_User = User.ID_User "
           "JOIN 'Group' ON User.ID_Group = 'Group'.ID_Group "
           "JOIN ThemeWork TW on LabWork.ID_Work = TW.ID_Theme "
           "JOIN WorkStatus WS on LabWork.Status = WS.ID_Status "
           "WHERE 'Group'.ID_Group = :id_group AND LabWork.ID_Work = :id_work AND WS.ID_Status = :id_status";
}

inline QString select_all_tests_results()
{
    return "SELECT 'Group'.Name_Group AS GroupName, User.ID_User, User.Fullname, "
            "TT.Name AS NameTest, Grade FROM ResultTest "
            "JOIN User ON ResultTest.ID_User = User.ID_User "
            "JOIN 'Group' ON User.ID_Group = 'Group'.ID_Group "
            "JOIN ThemeTest TT on ResultTest.ID_Theme = TT.ID_Theme";
}

inline QString select_all_tests_results_with_selections()
{
    return "SELECT 'Group'.Name_Group AS GroupName, User.ID_User, User.Fullname, "
           "TT.Name AS NameTest, Grade FROM ResultTest "
           "JOIN User ON ResultTest.ID_User = User.ID_User "
           "JOIN 'Group' ON User.ID_Group = 'Group'.ID_Group "
           "JOIN ThemeTest TT on ResultTest.ID_Theme = TT.ID_Theme "
           "WHERE 'Group'.ID_Group = :id_group AND TT.ID_Theme = :id_test AND Grade = :grade";
}

inline QString insert_lab_work()
{
    return "INSERT INTO LabWork (ID_User, ID_Work, TextWork, Status, Note) VALUES (:id_user, :id_work, :text_work, :id_status, :note)";
}

inline QString update_lab_work()
{
    return "UPDATE LabWork SET TextWork = :text_work, Status = :id_status, Note = :note WHERE ID_User = :id_user AND ID_Work = :id_work";
}

inline QString select_last_num_work()
{
    return "SELECT MAX(ID_Theme) AS LastNum FROM ThemeWork";
}

inline QString select_last_num_page()
{
    return "SELECT MAX(ID_Page) AS LastNum FROM TheoryPage";
}

inline QString insert_theory_page()
{
    return "INSERT INTO TheoryPage (ID_Page, Name_Page, Name_Theme, Path) VALUES (:id_page, :name_page, :name_theme, :path)";
}

inline QString insert_theme_work()
{
    return "INSERT INTO ThemeWork (ID_Theme, Name, Path) VALUES (:id_theme, :name_theme, :path)";
}

inline QString update_theme_work()
{
    return "UPDATE ThemeWork SET Name = :name_theme AND Path = :path WHERE ID_Theme = :id_theme";
}

#endif // SQL_REQUESTS

