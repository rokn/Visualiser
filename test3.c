int main(){
	int score;
	char grade;

	if(score >= 90){
		grade = 'A';
	}
	if(score >= 80 && score < 90){
		grade = 'B';
	}
	if(score >= 70 && score < 80){
		grade = 'C';
	}
	if(score >= 60 && score < 70){
		grade = 'D';
	}
	if(score >= 50 && score < 60){
		grade = 'E';
	}
	if(score < 50){
		grade = 'F';
	}
}