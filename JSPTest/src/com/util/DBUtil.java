package com.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class DBUtil {

	private static final String DRIVER="com.microsoft.sqlserver.jdbc.SQLServerDriver";
	private static final String URL="jdbc:sqlserver://localhost:1433;databaseName=userDB";
	private static final String USER="sa";
	private static final String PWD="Jb991015";
	
	static{
		try {
			Class.forName(DRIVER);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public static Connection getConnection(){
		try {
			return DriverManager.getConnection(URL,USER,PWD);
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}
	
	
	public static void closeAll(ResultSet rs,PreparedStatement ps,Connection conn){
		try {
			if(null!=rs)
				rs.close();
			if(null!= ps)
				ps.close();
			if(null!=conn)
				conn.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
	
}
