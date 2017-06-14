package com.bean;

public class FirstTitle {
	private int id;
	private String usnm;
	private String pswd;
	
	public FirstTitle(){
		
	}

	public FirstTitle(int id, String usnm, String pswd) {
		super();
		this.id = id;
		this.usnm = usnm;
		this.pswd = pswd;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getUsnm() {
		return usnm;
	}

	public void setUsnm(String usnm) {
		this.usnm = usnm;
	}

	public String getPswd() {
		return pswd;
	}

	public void setPswd(String pswd) {
		this.pswd = pswd;
	}
	
	

}
