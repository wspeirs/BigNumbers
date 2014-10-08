#!/usr/bin/perl -w

# constants
$numIterations = 10;
$outputFile = "output.txt";
$num1_size = 1;
$num2_size = 1;
@ops = ("a", "s", "m", "q", "o", "n", "g");

srand(0xBEDBEEF);
$totalTest = 0;
$errors = 0;

# remake the project
system("make clean");
system("make calc");

open($fh, ">$outputFile") or die $!;

#$fh = STDERR;

for($i = 0; $i < $numIterations; ++$i)
{

	for($num1_size = 1; $num1_size < 200; $num1_size += 5)
	{

		for($num2_size = 1; $num2_size < 200; $num2_size += 4)
		{
			# generate two numbers
			$num1 = GenerateNumber($num1_size);
			$num2 = GenerateNumber($num2_size);
			$zero = 0;
		
# 			$num1 = "1FD4";
# 			$num2 = "-764";
# 		
# 			print "NUM 1: $num1\nNUM 2: $num2\n";
# 			print `./calc n $num1 $num2`;
# 		
# 			next;
# 		
# 		
 			print STDOUT "IT: $i $num1_size  $num2_size\n";
		
			foreach $op (@ops)
			{
				CompareRes($num1, $num2, `./calc $op $num1 $num2`);
				CompareRes("-$num1", $num2, `./calc $op -$num1 $num2`);
				CompareRes($num1, "-$num2", `./calc $op $num1 -$num2`);
				CompareRes("-$num1", "-$num2", `./calc $op -$num1 -$num2`);
		
				# test against zeros
				CompareRes("$num1", "$zero", `./calc $op $num1 $zero`);
				CompareRes("$zero", "$num2", `./calc $op $zero $num2`);
				CompareRes("-$num1", "$zero", `./calc $op -$num1 $zero`);
				CompareRes("$zero", "-$num2", `./calc $op $zero -$num2`);
				CompareRes("$zero", "$zero", `./calc $op $zero $zero`);
			}
		}
	}
}

print $fh "TOTAL TEST: $totalTest\n";
print $fh "    ERRORS: $errors\n";
printf($fh "ERROR RATE: %d%%\n", ($errors/$totalTest)*100);

close($fh);


sub CompareRes
{
	chomp(@_);

	my $num1 = $_[0];
	my $num2 = $_[1];
	my $gmp  = $_[2];

	++$totalTest;

	for($j = 3; $j < @_; ++$j)
	{
		if($gmp ne $_[$j])
		{
			print $fh "OPERATION: $op:" . ($j-2) . "\nNUM 1: $num1\nNUM 2: $num2\nGMP : $gmp\nBIGNUM : $_[$j]\n\n";
			++$errors;
		}
	}
}

sub GenerateNumber
{
	my $size = $_[0];
	my $num = "";

	while($size > 0)
	{
		$num .= sprintf("%X", int(rand(0xFFFFFFFF)));
		$num = substr($num, 0, length($num) - int(rand(7)));
		--$size;
	}

	return $num;	
}
