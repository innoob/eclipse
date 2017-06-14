use [master]
go
if exists(select 1 from sys.databases where name='userDB')
drop database [userDB]
go
create database [userDB]
go
use [userDB]
go
create table [userinfo]
(
	[id] int not null identity(1,1) primary key,
	[username] nvarchar(32) not null,
	[password] nvarchar(64) not null,
)
go

insert into [userinfo] values(N'jason',N'123456')
go
select * from [userinfo]