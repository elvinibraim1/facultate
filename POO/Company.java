import java.util.ArrayList;

public class Company {
	public String companyName;
	public Manager manager;
	public ArrayList<Department> departments;
	public ArrayList<Recruiter> recruiters;
	
	public Company(String companyName) {
		this.companyName = companyName;
	}
	
	public void add(Department department) {
		departments.add(department);
	}
	
	public void add(Recruiter recruiter) {
		recruiters.add(recruiter);
	}
	
	public void add(Employee employee, Department deparment) { 
		deparment.add(employee);
	}
	
	public void remove(Employee employee) {
		for(Department department : departments) 
			for(Employee e : department.employees)
				if(e.equals(employee)) { 
					department.employees.remove(employee);
					break;
				}
		//itereaza in lista de de departamente, in fiecare departament cauta employee-ul dat ca paramentru dupa nume
		//cand angajatul este gasit, acesta este sters
	}
	
	public void remove(Department department) {
		department.employees.clear();
		departments.remove(department);
		//sterge toti angajatii, apoi departamentul;
	}
	
	public void remove(Recruiter recruiter) {
		recruiters.remove(recruiter);
	}
	
	public void move(Department source, Department destination) {
		for(Employee employee : source.employees)
			destination.add(employee);
		
		this.remove(source);
		//muta pe rand toti angajatii din sursa in destinatie, apoi sterge departamentul sursa
	}
	
	public void move(Employee employee, Department newDepartment) {
		this.remove(employee);
		
		newDepartment.employees.add(employee);
		//sterge angajatul din departament, apoi il muta in noul departament
	}

	public boolean contains(Department department) {
		return departments.contains(department);
	}
	
	public boolean contains(Employee employee) {
		for(Department department:departments)
			if(department.employees.contains(employee))
				return true;
		return false;
	}
	
	public boolean contains(Recruiter recruiter) {
		return recruiters.contains(recruiter);
	}
	
	public Recruiter getRecruiter(User user) {
		int degree = 0;
		int i = 0;
		int j = 0;
		
		for(Recruiter recruiter : recruiters) {
			if(degree <  recruiter.getDegreeInFriendship(user)) {
				degree = recruiter.getDegreeInFriendship(user);
				j = i;
			}
			
			if(degree == recruiter.getDegreeInFriendship(user))
				if(recruiters.get(i).rating > recruiters.get(j).rating)
					j = i;
			
			i++;
		}
		return recruiters.get(j);
		//cu variabila "i" se itereaza prin lista de recruiteri
		//cand se gaseste un recruiter cu distanta sociala mai mare, indicele se pastreaza in "j"
		//daca cea mai mare distanta sociala de pana acum, pastrata in variabila "degree" este egala cu distanta sociala a recruiterului care este verificat la pasul i
		//se pastreaza in j indicele recruiter-ului cu rating mai mare
		//in final functia returneaza recruiterul de pe pozitia j din lista
	}
	
	public ArrayList<Job> getJobs() {
		ArrayList<Job> jobs = new ArrayList<Job>();
		
		for(Department department : departments)
			jobs.addAll(department.getJobs());
			
		return jobs;	
		//pentru fiecare departament al companiei, se adauga in lista "jobs", joburile deschise cu functia "getJobs" din clasa "Department"
		//se returneaza lista "jobs"
	}
}

abstract class Department {
	public ArrayList<Employee> employees = new ArrayList<Employee>();
	public ArrayList<Job> jobs = new ArrayList<Job>();
	
	public abstract double getTotalSalaryBudget();
	
	public ArrayList<Job> getJobs() {
		ArrayList<Job> j = new ArrayList<Job>();
		for(Job job : this.jobs)
			if(job.flag == true)
				j.add(job);
		
		return j;
		//returneaza joburile deschise din acest departament			
	}
	
	public void add(Employee employee) {
		employees.add(employee);
	}
	
	public void remove(Employee employee) {
		employees.remove(employee);
	}
	
	public void add(Job job) {
		jobs.add(job);
	}
	
	public ArrayList<Employee> getEmployees() {
		return employees;
	}
}

class IT extends Department {
	public double getTotalSalaryBudget() {
		double totalSalary = 0.0;
		
		for(Employee employee : employees)
			totalSalary = totalSalary + employee.salary;
		
		return totalSalary;
	}	
}

class Management extends Department {
	public static double tax = 0.16;

	public double getTotalSalaryBudget() {
		double totalSalary = 0.0;
		
		for(Employee employee : employees)
			totalSalary = totalSalary + employee.salary * (1 + tax);
		
		return totalSalary;
	}
}

class Marketing extends Department {
	public static double tax1 = 0.10;
	public static double tax2 = 0.16;

	public double getTotalSalaryBudget() {
		double totalSalary = 0.0;
		
		for(Employee employee : employees) {
			if(employee.salary > 5000)
				totalSalary = totalSalary + employee.salary * (1 + tax1);
			if(employee.salary < 3000)
				totalSalary = totalSalary + employee.salary;
			else totalSalary = totalSalary + employee.salary * (1 + tax2);				
		}
		
		return totalSalary;
	}
}

class Finance extends Department {
	public static double tax1 = 0.10;
	public static double tax2 = 0.16;

	public double getTotalSalaryBudget() {
		double totalSalary = 0.0;
		int experience = 0;	
		
		for(Employee employee : employees) {
			experience = employee.getExperience();
		
		if(experience < 1)			
			totalSalary = totalSalary + employee.salary * (1 + tax1);
		else totalSalary = totalSalary + employee.salary * (1 + tax2);
	}
		
		return totalSalary;
	}
}

class departmentFactory {
	
	public static Department createDepartment(String type) {
		if(type.equals("IT")) {
			IT IT = new IT();
		return IT;
		}
		
		if(type.equals("Management")) {
			Management management = new Management();
		return management;
		}
		
		if(type.equals("Marketing")) {
			Marketing marketing = new Marketing();
		return marketing;
		}
		
		if(type.equals("Finance")) {
			Finance finance = new Finance();
		return finance;
		}
		
		return null;		
	}
}