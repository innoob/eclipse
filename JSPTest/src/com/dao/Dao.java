package com.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import com.bean.FirstTitle;
import com.util.DBUtil;

public class Dao {
	private Connection conn = null;
	private ResultSet rs = null;
	private PreparedStatement ps = null;

	public ArrayList<FirstTitle> findAll(){
		try {
			conn = DBUtil.getConnection();
			String sqlcmd = "select * from userinfo";
			ArrayList<FirstTitle> list =new ArrayList<FirstTitle>();
			ps=conn.prepareStatement(sqlcmd);
			rs=ps.executeQuery();
			while(rs.next()){
				list.add(new FirstTitle(rs.getInt("id"),rs.getString("username"),rs.getString("password")));
			}
			return list;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}finally{
			DBUtil.closeAll(rs, ps, conn);
		}
	}
	
	public boolean checkUser(String username,String password){
		try {
			conn=DBUtil.getConnection();
			String sqlcmd = "select 1 from userinfo where username=? and password=? ";
			ps=conn.prepareStatement(sqlcmd);
			ps.setString(1, username);
			ps.setString(2,password);
			return ps.executeQuery().next();
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}finally{
			DBUtil.closeAll(rs, ps, conn);
		}
	}
}
