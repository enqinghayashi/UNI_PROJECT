
#Student Name: Enqing Lin

#Task:
#This program need to analyse a CSV file and create a dictionary and calculate the following statiscal informaion to store in it:
# Calculate standard error of population for each region and calculate the cosine similarity between population and land area for each region.
# Create a major dictionary that contains region(keys) and for each country(values) in the region, a sub. The information required is stored in a list
# [population, net change, percentage of population with respect to a region, density of population, and rank of population in the region]. With that list being the value
# of sub-dictionaries. e.g. {region: {country: [information lists]}}

#Pseudocodes:
# Output1: standard error of population for each region and the cosine similarity between population and land area for each region. Region names as the keys and information list as values
#          for sub-dictionaries
#          1. Write a function that extracts population, land area, regional area and number of countries for a region from the file. Then calculate standard deviation in order to calculate standard error,
#             and calculate cosine similarity. Then store the standard error and cosine similarity value in a list, [standard error, cosine similarity].
#          2. Write a function that read all the regions in the files and use for loops and use step 1 function to return information list for each region automatically and returns a
#             dictionaries with regions name as the keys and information list as values. e.g. {Region: [information list]}
# Output2: {region: {country: [information lists]}}, information list=[population, net change, percentage of population with respect to a region, density of population, and rank of population in the region]
#          1. Write a function that extract population and net change data of each country in a region and store them in the list.
#          2. Write a function that calculates percentage of population with respect to a ergion
#          3. Write a function that calculates density of population in a country
#          4. Write a function that calculates rank of population of the country in the region
#          5. Append the outputs of step 2-4 to step 1's list
#          6. Make 2 empty dictionaries, first one for storing {countries: [information list]}, second one for equating 'first dictionaries' as values to second dictionaries. e.g. {region: {countries: [information list]}}
#          7. Write a function that read all the regions in the files and use for loops to automate run each region through 1-6

            #Output1 Codes
def output1_values(data,region): #comments: This function makes the information list for first output dictionaries, {Region: [information list]}
    Population = [] #comments: for the purpose of storing each population value in the region as a list
    landarea = [] #comments: for the purpose of storing each land areas value in the region as a list
    AB_list=[] #comments: Population is A, Landarea is B. For the purpose of storing A*B value in the region as a list
    SD_numerator = 0.0 #comments: for the purpose to store values
    regional_population = 0.0
    Asquare = 0.0
    Bsquare = 0.0
    for row in data:
        Regions=row["Regions"]
        if Regions.casefold() == region.casefold():
            Population.append(int(row["Population"]))
            landarea.append(int(row["Land Area"]))
        num_countries = len(Population)
    for num in Population:
        regional_population += num #comments: finding the regional population
        num **= 2
        Asquare += num 
    for area in landarea:
        area **= 2
        Bsquare += area
    for x in range(len(Population)):
        AB_list.append(Population[x]*landarea[x]) #comments: A*B list is stored
    average = regional_population/num_countries
    det = [x-average for x in Population] 
    for i in det:
        i *= i
        SD_numerator += i
            
    SD = round((SD_numerator/(num_countries-1))**(1/2),4) #comments: standard deviation calculated
    similarity=round((sum(AB_list))/((Asquare**0.5)*(Bsquare**0.5)),4)
    standard_error = round(SD/(num_countries**(1/2)),4)
    
    return [standard_error, similarity] #comments: information list

def output1(data): #comments: step 2 for Output1, a function that make the dictionaries {Region: [information list]} and can automate analyse information list for each region
    dict1 = {} #comments: empty dictionaries to store the values(information list)
    region_list = []
    for row in data:
        region_list.append(row["Regions"])
        region_set = set(region_list) #comments: use set to eliminate duplicate region names
        region_set.discard("Regions") #comments: the functions reads all lines in the file which also included the headers "Regions", which needs to be removed from the region set
    for names in region_set:
        region = names.casefold()
        dict1[region]=output1_values(data,region) #comments: dictionaries made
    
    return dict1

            #Output2 Codes
def country_density(data,country): #comments: density for country name given
    country_data = [row for row in data if row["Country"].casefold() == country.casefold()]
    P = float(country_data[0]["Population"])
    L = float(country_data[0]["Land Area"])
    D = round(P/L,4)

    return D

def ranklist_by_population(data,region):
    ranking_list = []
    for row in data:
        if row["Regions"].casefold() == region.casefold():
            ranking_list.append([row["Country"], int(row["Population"])])
    ranking_list.sort(key = lambda x:-x[1]) #comments: sort by descending order of population
    
    return ranking_list

def regional_population(data,region): #comments: I realised regional population will be a bit complicated to calculate in output2_values(Files,country), so this def function is created
    Population = []
    for row in data:
        if row["Regions"].casefold() == region.casefold():
            Population.append(float(row["Population"]))
                
    return sum(Population)
                
def countriesList_in_region(data,region): #comments: a function that can pull out all the country name in a region and store it as list
    countriesList=[]
    for row in data:
        if row["Regions"].casefold() == region.casefold():
            countriesList.append(row["Country"])
                
    return countriesList

def output2_values(data,country): #comments: This function makes the information list for second output dictionaries 
    value2=[] #comments: the values for second output dictionaries
    sub_dict={} #comments: empty dictionaries for sub-dictionaries in the second ouput dictionaries
    dict2={} # second output dictionaries
    for row in data:
        if row["Country"].casefold() == (str(country)).casefold():
            country_population = int(row["Population"]) #comments: population data collected
            net_change = int(row["Net Change"]) #comments: net change data collected 
            region = row["Regions"] #region name is defined
            Regional_population = regional_population(data,region) #since region name is defined, Regional population can be calculated
            percentage = round((country_population / Regional_population) * 100 , 4) #comments: % of population with respect to region calculated
            density = country_density(data,country) #comments: density calculated
            ranklist = ranklist_by_population(data,region) #comments: ranklist defined
            rank = ranklist.index([row["Country"], country_population]) + 1 #comments: country's ranking in the region by population calculated
            value2.extend([country_population, net_change,percentage, density, rank]) #comments: information list for sub-dictionaries created
            sub_dict[country.casefold()] = value2 #comments: sub-dictionaries created
            dict2[region]=sub_dict #comments: second output dictionaries created
                
    return dict2

def output2(Files, data): #comments: This function is to run automated analyse for second output and combine the dictionaries in 'second output dictionaries' into one when the dictionaries have the same keys(region names) 
    region_list=[]  #          beacause I realised my dict2 which is the 'second output dictionaries' is not combined, it have dictionaries each line with the same keys.
    output2_dict2_list=[] #comments: make the uncombined second output dictionaries as a list can help with the combination of dictionaries
    output2_result={} #comments: combined second output dictionaries
    with open(Files, 'r', encoding = 'UTF 8') as fread:
        for line in fread:
            info=line.split(',')
            region_list.append((info[7]).strip())
    region_set=set(region_list)
    region_set.discard("Regions")
    for name in region_set:
        region = name
        countries_list=countriesList_in_region(data, region)
        for country in countries_list:
            output2_dict2_list.append(output2_values(data,country)) #comments: list created
        for dictionary in output2_dict2_list:
            keys = list(dictionary.keys())[0].casefold() #keys defined
            values = list(dictionary.values())[0] #values defined, ie the sub-dictionaries
            if keys in output2_result:  
                output2_result[keys].update(values) 
            else:
                output2_result[keys] = values
                
    return output2_result
    

def read_data(Files): #comments: to open the file just once
    data = []
    lines = set() #comments: remove duplicate lines
    with open(Files, "r", encoding="UTF 8") as fread:
        headers = [header.strip() for header in fread.readline().split(',')]
        for line in fread:
            if line not in lines:  #comments: check for duplicate lines
                lines.add(line)
                values = line.split(',')
                data.append(dict(zip(headers, [value.strip() for value in values])))
    return data

def main(Files):
    data = read_data(Files)
    return output1(data), output2(Files, data)
    
        
            