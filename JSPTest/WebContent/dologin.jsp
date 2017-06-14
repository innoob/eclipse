<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%@page import="com.bean.*,com.util.*,com.dao.*,java.util.*" %>
	<%  String usnm = request.getParameter("usnm");
		String pswd = request.getParameter("pswd");
	%>
	<%
		Dao dao  = new Dao();
		ArrayList<FirstTitle> list = dao.findAll();
		Iterator<FirstTitle> it  = list.iterator();
		FirstTitle ft = it.next();
		if(dao.checkUser(usnm, pswd)){
			request.getRequestDispatcher("index.jsp").forward(request, response);
		}
		request.getRequestDispatcher("error.jsp").forward(request, response);
	%>
</body>
</html>