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

inline QString select_theme_test()
{
    return "SELECT * FROM ThemeTest WHERE ID_Theme = :id_theme";
}

inline QString select_question()
{
    return "SELECT * FROM Question WHERE ID_Question = :id_question AND ID_Theme = :id_theme";
}

inline QString select_answer_of_question()
{
    return "SELECT * FROM AnswerToQuestion WHERE ID_User = :id_user AND ID_Theme = :id_theme AND ID_Question = :id_question";
}

inline QString insert_answer_of_question()
{
    return "INSERT INTO AnswerToQuestion (ID_User, ID_Theme, ID_Question, Answer) VALUES (:id_user, :id_theme, :id_question, :id_answer)";
}

inline QString update_answer_of_question()
{
    return "UPDATE AnswerToQuestion SET Answer = :id_answer WHERE ID_User = :id_user AND ID_Theme = :id_theme AND ID_Question = :id_question";
}

inline QString insert_test_result()
{
    return "INSERT INTO ResultTest (ID_User, ID_Theme, Grade, Date) VALUES (:id_user, :id_theme, :grade, :date)";
}

inline QString update_test_result()
{
    return "UPDATE ResultTest SET Grade = :grade, Date = :date WHERE ID_User = :id_user AND ID_Theme = :id_theme";
}

inline QString select_test_result()
{
    return "SELECT * FROM ResultTest WHERE ID_User = :id_user AND ID_Theme = :id_theme";
}

inline QString select_test_results_for_user()
{
    return "SELECT ThemeTest.ID_Theme, ThemeTest.Name, Grade, ResultTest.Date "
              "FROM ResultTest "
              "JOIN ThemeTest ON ResultTest.ID_Theme = ThemeTest.ID_Theme WHERE ID_User = :id_user";
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
            "TT.ID_Theme, TT.Name AS NameTest, Grade, Date FROM ResultTest "
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
    return "INSERT INTO LabWork (ID_User, ID_Work, TextWork, Status, Note, DateDelivery) "
           "VALUES (:id_user, :id_work, :text_work, :id_status, :note, strftime('%d-%m-%Y', :date))";
}

inline QString update_lab_work()
{
    return "UPDATE LabWork SET TextWork = :text_work, Status = :id_status, Note = :note, DateDelivery = strftime('%d-%m-%Y', :date) "
           "WHERE ID_User = :id_user AND ID_Work = :id_work";
}

inline QString select_last_num_work()
{
    return "SELECT MAX(ID_Theme) AS LastNum FROM ThemeWork";
}

inline QString select_last_num_theory_page()
{
    return "SELECT MAX(ID_Page) AS LastNum FROM TheoryPage";
}

inline QString select_last_num_test()
{
    return "SELECT MAX(ID_Theme) AS LastNum FROM ThemeTest";
}

inline QString select_last_num_help_page()
{
    return "SELECT MAX(ID_Page) AS LastNum FROM HelpPage";
}

inline QString insert_theory_page()
{
    return "INSERT INTO TheoryPage (ID_Page, Name_Page, Name_Theme, Path) VALUES (:id_page, :name_page, :name_theme, :path)";
}

inline QString insert_theme_work()
{
    return "INSERT INTO ThemeWork (ID_Theme, Name, Path, Deadline) VALUES (:id_theme, :name_theme, :path, strftime('%d-%m-%Y', :deadline))";
}

inline QString update_theme_work()
{
    return "UPDATE ThemeWork SET Name = :name_theme, Path = :path, Deadline = strftime('%d-%m-%Y', :deadline) WHERE ID_Theme = :id_theme";
}

inline QString insert_theme_test()
{
    return "INSERT INTO ThemeTest (ID_Theme, Name, NumberOfQuestions) VALUES (:id_theme, :name_theme, :number_questions)";
}

inline QString update_theme_test()
{
    return "UPDATE ThemeTest SET Name = :name_theme, NumberOfQuestions = :number_questions WHERE ID_Theme = :id_theme";
}

inline QString insert_question()
{
    return "INSERT INTO Question (ID_Theme, ID_Question, Text_Question, Answer_1, Answer_2, Answer_3, Answer_4, Right_Answer) "
           "VALUES (:id_theme, :id_question, :text_question, :answer_1, :answer_2, :answer_3, :answer_4, :right_answer)";
}

inline QString update_question()
{
    return "UPDATE Question SET Text_Question = :text_question, Answer_1 = :answer_1,  Answer_2 = :answer_2, Answer_3 = :answer_3, "
           "Answer_4 = :answer_4, Right_Answer = :right_answer WHERE ID_Theme = :id_theme AND ID_Question = :id_question";
}

inline QString select_instruction_file()
{
    return "SELECT * FROM InstructionPage WHERE ID_Page = :id_page";
}

inline QString select_user_help_page_by_id()
{
    return "SELECT * FROM UserHelpPage WHERE ID_Page = :id";
}

inline QString select_user_help_page_by_name()
{
    return "SELECT * FROM UserHelpPage WHERE Name_Theme = :name";
}

inline QString select_admin_help_page_by_id()
{
    return "SELECT * FROM AdminHelpPage WHERE ID_Page = :id";
}

inline QString select_admin_help_page_by_name()
{
    return "SELECT * FROM AdminHelpPage WHERE Name_Theme = :name";
}

inline QString select_all_rgb_colors()
{
    return "SELECT * FROM RGBColor";
}

inline QString select_rgb_color()
{
    return "SELECT * FROM RGBColor WHERE ID_Color = :id_color";
}

inline QString select_all_formats_files()
{
    return "SELECT * FROM FormatFile";
}

inline QString select_format_file()
{
    return "SELECT * FROM FormatFile WHERE ID_Format = :id_format";
}

inline QString select_used_formats_files()
{
    return "SELECT * FROM FormatFile WHERE Used = 1";
}

inline QString insert_format_file()
{
    return "INSERT INTO FormatFile (Name, Used) VALUES (:name, :used)";
}

inline QString update_format_file()
{
    return "UPDATE FormatFile SET Name = :name, Used = :used WHERE ID_Format = :id";
}

inline QString select_system_options()
{
    return "SELECT * FROM SystemOptions WHERE ID_Record = 1";
}

inline QString update_system_options()
{
    return "UPDATE SystemOptions SET UseMoreTheoryPages = :use_more_theory, NumberPrimaryPage = :number_primary, "
           "UseCopySelectPage = :use_copy_select, UseSelectPageInList = :use_select_page, NumberColorSelectedPage = :number_color_select, "
           "UseDeadLineWork = :use_deadline, NumberDefaultFormatFile = :number_format_file, UseSomeFormatFile = :use_some_format, "
           "FormatFileList = :format_file, AllowDeliveryWorkAfterEndTerm = :allow_delivery_work, UseHintsInTest = :use_hints, "
           "NumberHints = :number_hints, UseViewResult = :use_view_result, UseRepeatPassage = :use_repeat_passage, "
           "UseTimer = :use_timer, TimerValue = :value_timer WHERE ID_Record = 1";
}

#endif // SQL_REQUESTS

