def main(Files,region):
#Question 1 variables
    Population_list2=[]
    most_populated_country=None
    least_populated_country=None
#Question 2 variables
    Population_list1=[]
    SD_numerator=0.0
    regional_population=0.0
    number_of_countries=None
#Question 3 variables
    data_in_file=[]
    density=[]
#Question 4 variables
    area_list=[]
    area_square=[]
    population_square=[]
    population_average=None
    area_average=None
    population_list=[]
    new_area_list=[]
    population_x_area_list=[]
    with open(Files,"r") as fread:
#comment: redefine all the variable first
        
#mostly Q1 works, some Q2 and Q4 works
        for line in fread:
            info=line.split(',')
            Regions=str(info[5][0:2])
            Net_Change=info[3]
            if Regions==region[0:2]:
                Population_list1.append(float(info[1]))
                number_of_countries=len(Population_list1)
                data_in_file.append(info)
                area_list.append(float(info[4]))
                if int(Net_Change)>0:
                    Population_list2.append(int(info[1]))
                    minPopulation=min(Population_list2)
                    maxPopulation=max(Population_list2)
                if int(info[1])==maxPopulation:
                    most_populated_country=info[0]
                elif int(info[1])==minPopulation:
                    least_populated_country=info[0]
        population_average=sum(Population_list1)/len(Population_list1)
        area_average=sum(area_list)/len(area_list)
#Q2 work starts from here         
    for num in Population_list1:
        regional_population += num
        average=regional_population/number_of_countries
        det=[x-average for x in Population_list1]
    for i in det:
        i *= i
        SD_numerator += i
#Q3 work starts from here
    for columns in data_in_file:
        population_size=float(columns[1])
        land_area=float(columns[4])
        D=round(population_size/land_area,4)
        y=[str(columns[0]),D]
        density.append(y)
#Q4 works starts from here
    for num in area_list:
        num -= area_average
        area_sqr=num**2
        area_square.append(area_sqr)
        new_area_list.append(num)
    for num in Population_list1:
        num -= population_average
        population_sqr=num**2
        population_square.append(population_sqr)
        population_list.append(num)
    for p in range(len(population_list)):
        population_x_area_list.append(population_list[p]*new_area_list[p])
#After all the variables for each question is redefined, then assign the varaible to a new string. For me, it's MaxMin, stdvAverage, density and correlation        
#Q1 answer
    MaxMin=[most_populated_country,least_populated_country]
#Q2 answer  
    SD=round((SD_numerator/(number_of_countries-1))**(1/2),4)
    stdvAverage=([round(average,4),SD])
#Q3 answer
    density=sorted(density,key=lambda x:-x[1])
#Q4 answer
    numerator=sum(population_x_area_list)
    denominator=((sum(population_square)*sum(area_square)))**(1/2)
    correlation=round(numerator/denominator,4)
    
    return MaxMin, stdvAverage, density, correlation

