import java.util.Date;
import java.util.HashMap;

public class Information {
	private String surName;
	private String firstName;
	private String email;
	private String phoneNumber;
	private Date date;
	private char sex;
	private HashMap<String, String> languages;

	public String getSurName() {
		return surName;
	}

	public void setName(String surName) {
		this.surName = surName;
	}
	
	public String getFirstName() {
		return firstName;
	}
	
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}
	
	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}
	
	public String getPhoneNumber() {
		return phoneNumber;
	}
	
	public void setPhoneNumber(String phoneNumber) {
		this.phoneNumber = phoneNumber;
	}
	
	public Date getDate() {
		return date;
	}
	
	public void setDate(Date date) {
		this.date = date;
	}
	
	public char getSex() {
		return sex;
	}
	
	public void setSex(char sex) {
		this.sex = sex;
	}
	
	public HashMap<String, String> getLanguages() {
		return languages;
	}
	
	public void setLanguages(HashMap<String, String> languages) {
		this.languages = languages;
	}
}
