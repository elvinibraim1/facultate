import java.util.ArrayList;

public class Job {
	public String jobName;
	public String companyName;
	public boolean flag = true;
	public Constraint graduation;
	public Constraint experience;
	public Constraint avgGrade;
	public ArrayList<User> candidates;
	public int noPositions;
	public Double salary;
	
	public Job(int noPositions, Double salary, Constraint graduation, Constraint experience, Constraint avgGrade) {
		this.noPositions = noPositions;
		this.salary = salary;
		this.graduation = graduation;
		this.experience = experience;
		this.avgGrade = avgGrade;
	}
	
	public void apply(User user) {
		if(flag == true)
			Aplication.getInstance().getCompany(this.companyName).getRecruiter(user).evaluate(this, user);

		//cauta cu "getComaany" compania, in functie de nume, apoi recruiterul potrivit din companie, in functie de user
		//recruiter care evalueaza userul ( evaluate(this, user)
	}
	
	public boolean meetsRequirments(User user) {
		if(user.getGraduationYear() >= graduation.min && user.getGraduationYear() <= graduation.max)
			if(user.getExperience() >= experience.min && user.getExperience() <= experience.max)
				if(user.meanGPA() >= avgGrade.min && user.meanGPA() <= avgGrade.max)
					return true;
		return false;
		//verifica pe rand daca user-ul dat se incadreaza in toate cele 3 constrangeri, in caz contrar returneaza fals
	}
}

class Constraint {
	public int min;
	public int max;
	
	public Constraint(int min, int max) {
		this.min = min;
		this.max = max;
	}
}
