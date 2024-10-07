// //
// // Created by 李勃鋆 on 24-10-5.
// //
// #include <workflow/WFFacilities.h>
// #include <workflow/MySQLUtil.h>
// #include <workflow/MySQLResult.h>
// #include <iostream>
// #include <signal.h>
// using std::string;
// using std::cerr;
// static WFFacilities::WaitGroup waitGroup(1);//静态变量，在全局静态区，整个程序范围
// void sighandler(int signum){//信号处理函数的回调函数
//     std::cout << "signum = " << signum << "\n";
//     waitGroup.done();//减少waitGroup的数量，每次减少一个，为0时结束
// }
// void mysqlCallback(WFMySQLTask * mysqlTask){//数据库任务的回调函数
//     if(mysqlTask->get_state() != WFT_STATE_SUCCESS){
//         // 在系统层面报错，权限or密码
//         cerr << "error_msg =  " << WFGlobal::get_error_string(mysqlTask->get_state(), mysqlTask->get_error()) << "\n";
//         return;
//     }
//     protocol::MySQLResponse * resp = mysqlTask->get_resp();//获取响应对象，提取执行 MySQL 查询后的结果
//     if(resp->get_packet_type() == MYSQL_PACKET_ERROR){//检查MySQL的状态
//         // 在SQL语句报错
//         cerr << "error_code = " << resp->get_error_code() << " error_msg = " << resp->get_error_msg() << "\n";
//         return;
//     }
//     protocol::MySQLResultCursor cursor(resp);//遍历查询结果的迭代器
//     do{
//         if(cursor.get_cursor_status() == MYSQL_STATUS_OK){
//             // 写类型的SQL语句
//             cerr << "write \n";
//             cerr << cursor.get_affected_rows() << " rows affected\n";//SQL 语句执行时受影响的行数
//         }
//         else if(cursor.get_cursor_status() == MYSQL_STATUS_GET_RESULT){
//             // 读类型的SQL语句
//             cerr << "read \n";
//             // 读表头 列的信息 field
//             const protocol::MySQLField * const * fieldArr;
//             fieldArr = cursor.fetch_fields();//获取表中的字段
//             for(int i = 0; i < cursor.get_field_count(); ++i){
//                 cerr << "db = " << fieldArr[i]->get_db()//数据库名
//                      << " table = " << fieldArr[i]->get_table()//表名
//                      << " name = " << fieldArr[i]->get_name()//字段名
//                      << " type = " << datatype2str(fieldArr[i]->get_data_type()) << "\n";//字段树类型
//             }
//             // 读表的内容 每一行每一列
//             // bool fetch_all(std::vector<std::vector<MySQLCell>>& rows);
//             std::vector<std::vector<protocol::MySQLCell>> rows;
//             cursor.fetch_all(rows);
//             for(auto &row:rows){//读取每一行
//                 for(auto &cell:row){//读取每一行中的每一列
//                     if(cell.is_int()){
//                         cerr << cell.as_int();
//                     }
//                     else if(cell.is_string()){
//                         cerr << cell.as_string();
//                     }
//                     else if(cell.is_datetime()){
//                         cerr << cell.as_datetime();
//                     }
//                     cerr << "\t";
//                 }
//                 cerr << "\n";
//             }
//         }
//     }while(cursor.next_result_set()); //mysql 任务支持一个任务处理多个SQL语句
// }
// int WF_test02_03(){
//     signal(SIGINT,sighandler);
//     WFMySQLTask * mysqlTask =  WFTaskFactory::create_mysql_task("mysql://root:123@localhost",1,mysqlCallback);//创建mysql任务
//     string sql = "insert into mycloud.tbl_user_token (user_name,user_token) values ('Caixukun','singdancerap');";//sql语句
//     //string sql;
//     sql += "select * from mycloud.tbl_user_token;";
//     mysqlTask->get_req()->set_query(sql);//添加sql语句到任务中
//     mysqlTask->start();
//     waitGroup.wait();
//     return 0;
// }