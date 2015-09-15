#!/usr/bin/awk -f

BEGIN {FS = " "; ham=0; spam=0; total_spam_score=0; infected=0;}

#Assumes all emails have a "Checking" line. Extracts emails from line and adds to list.
/Checking/ {
from_index=-1
to_index=-1
for(i=1; i<=NF; i++)
	if ($i ~ /@/)
		if(from_index<0) 
			from_index=i
		else if(to_index<0) 
			to_index=i
if(from_index>0)
	senders[$from_index]+=1
if(to_index>0)
	receivers[$to_index]+=1



}

/Passed CLEAN/ {ham++}
/Blocked SPAM/ {spam++}
/Blocked INFECTED/ {infected++}
/Hits:/ {total_spam_score+= substr($18, 0, length($18)-1)}

#Searches through any list ls and returns a top 10 list (tor) based on the values of ls.
function get_top(tor,ls)
{
for(item in ls) cp[item]=ls[item]
for (i=0; i<10; i++){
        maxval=-1
        maxindex=""
        for(item in cp)
                if (cp[item]>maxval){
                        maxval=cp[item]
                        maxindex=item}
        tor[maxindex]=maxval
        delete cp[maxindex]

}


}


END {

send=get_top(top_senders, senders)
rec=get_top(top_receivers, receivers)

print "10 top senders"
print "--------------"
for(item in top_senders)
	print substr(item, 2, length(item)-2), top_senders[item]
print "\n10 top recipients"
print "--------------"
for(item in top_receivers)
	print substr(item, 2, length(item)-2), top_receivers[item]

print "\nStats"
print "--------------"
printf "%s%d\n", "Ham: ", ham 
printf "%s%d\n", "SPAM: ", spam
printf "%s%f\n", "Average SPAM score: ", (total_spam_score/spam)
printf "%s%f\n", "SPAM to Ham ratio: ", (spam/ham)
printf "%s%d\n", "Infected: ", infected

}	
