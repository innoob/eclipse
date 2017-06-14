<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" errorPage="error.jsp"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<style type="text/css">
	#title{
	width:100%;
	text-align:center;
	}
	div{
	margin-top:10px
	}
	.input-line{
	width:100%;
	height:50px;
	text-align:center;
	}
	div>span{
	width:80px;
	height:30px;
	line-height:30px;
	display:inline-block;
	}
	input[type="submit"]{
	width:90px;
	height:30px;
	}
</style>
</head>
<body>
	<form action="dologin.jsp" method="post">
	<div id="title">
		<h1>User Login</h1>
	</div>
	<hr>
	<div class="input-line">
		<div>
			<span>Username</span>
			<input type="text" name="usnm">
		</div>
		<div>
			<span>Password</span>
			<input type="password" name="pswd">
		</div>
		<div>
			<input type="submit" value="login">
		</div>
	</div>
	</form>
</body>
</html>