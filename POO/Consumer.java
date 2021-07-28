import java.time.LocalDate;
import java.time.Period;
import java.util.*;

public abstract class Consumer {
	public Resume resume;
	public ArrayList<Consumer> friends = new ArrayList<Consumer>();
	
	public void add(Education education) {
		resume.getEducations().add(education);
	}
	
	public void add(Experience experience) {
		resume.getExperiences().add(experience);
	}
	
	public void add(Consumer consumer) {
		friends.add(consumer);
	}
	
	public int getDegreeInFriendship(Consumer consumer) {
		return 10;
	}
	
	public void remove(Consumer consumer) {
		friends.remove(consumer);
	}
	
	public Integer getGraduationYear() {
		for(Education education : resume.getEducations())
			if(education.level.compareTo("College") == 0 && education.end != null)			
					return education.end.getYear();
		return null;
		//iterez prin lista de educatii din resume, daca gasesc ciclul de educatie "College", returnez anul absolvirii
		//in cazul in care "College" nu exista sau este inca in curs,  se returneaza null
	}
	
	public Double meanGPA() {
		Double avg = 0.0;
		for(Education education: resume.getEducations())
			avg = avg + education.avgGrade;
		return avg/resume.getEducations().size();
		//pentru fiecare educatie se aduna media generala(avgGrade), apoi se imparte la numarul de educatii
	}
	
	public int getExperience() { //functie auxiliara
		int totalExperience = 0;
		for(Experience experience : resume.getExperiences()) {
			if(experience.end == null)
				experience.end = LocalDate.now();
			
			int months = Period.between(experience.start, experience.end).getMonths();
			
			while(months >= 3) {
				totalExperience = totalExperience + 1;
				months = months - 12;
			}
		}
		
		return totalExperience;
		//itereaza in lista de experiente si pentru fiecare salveaza in variabila "months" numarul de luni dintre data de inceput si data de final
		//cum se aproximeaza prin adaos la un an pentru o perioada de peste 3 luni, incrementez  experience si scad din months 12, pana cand months este < 3
	}
}

class ResumeIncompleteException extends  Exception {
	public ResumeIncompleteException(String mesaj) {
		super(mesaj);
	}
}

class Resume {
	private Information information;
	private TreeSet<Education> educations = new TreeSet<Education>();
	private TreeSet<Experience> experiences = new TreeSet<Experience>();
	
	private Resume(ResumeBuilder builder) {
		this.information = information;
		this.educations = educations;
		this.experiences = experiences;
	}
	
	public Information getInformation() {
		return information;
	}
	
	public TreeSet<Education> getEducations() {
		return educations;
	}
	
	public TreeSet<Experience> getExperiences() {
		return experiences;
	}
	
	public static class ResumeBuilder {
		private Information information;
		private TreeSet<Education> educations = new TreeSet<Education>();
		private TreeSet<Experience> experiences = new TreeSet<Experience>();
		
		public ResumeBuilder information (Information information) {
			this.information = information;
			return this;
		} 
		
		public ResumeBuilder educations(TreeSet<Education> educations) {
			this.educations = educations;
			return this;
		}
		
		public ResumeBuilder experiences(TreeSet<Experience> experiences) {
			this.experiences = experiences;
			return this;
		}
		
		public Resume Build() throws ResumeIncompleteException {
			return new Resume(this);
		}
	}
	
}

class User extends Consumer {
	List<String> companies = new ArrayList<String>();
	
	public User (List<String> companies) {
		this.companies = companies;
	}

	public Employee convert() {
		Employee employee = new Employee();
		employee.resume = this.resume;
		employee.friends = this.friends;
		
		return employee;
	}
	
	public Double getTotalScore() {
		
		return getExperience() * 1.5 + meanGPA();
		//folosim functia auxiliara pentru returnarea scorului
	}
}

class Employee extends Consumer {
	public String companyName;
	public Double salary;
	
	public void setCompanyName(String companyName) {
		this.companyName = companyName;
	}
	
	public void setSalary(Double salary) {
		this.salary = salary;
	}
}

class Recruiter extends Employee {
	public float rating = 5;
	
	public Manager manager = Aplication.getInstance().getCompany(this.companyName).manager;

	public int evaluate(Job job, User user) {		
		manager.requests.add(new Request(job, user, this, (rating * user.getTotalScore())));
		rating = rating + 0.1f;
		
		return (int)((rating - 0.1f) * user.getTotalScore());
		//metoda adauga un nou request in lista de requesturi din clasa manager
		//rating-ul recruiter-ului creste cu 0.1, apoi metoda returneaza scorul obtinut de user (cu rating-ul initial)
	}
}

class Manager extends Employee {
	
	ArrayList<Request> requests = new ArrayList<Request>();

	public void process(Job job) {
		Collections.sort(requests);
			}
}
