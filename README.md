Caution: This mini peoject is my first hands on exerience in the field, and should be considered far from being perfect.

The repository contains an implementation of non-linear support vector regression,
using gaussian kernel, without using any library except c++ STL, for better understanding of the method.

The aim is to predict next year rainfall based on previous year data. 
The dataset has been made available by Government of India and can be found at the following link: https://data.gov.in/catalog/district-rainfall-normal-mm-monthly-seasonal-and-annual-data-period-1951-2000

A model is trained is tarained for each state, for each state to predict the upcoming year rainfall.

Method use:
    Data prepocessing:
        The missing data points are filled by the average rainfall of the month for the given state.
        Then a feature matrix is prepared by normalising the columns of the matrix, month by month.
        Gaussian kernel is then applied.

    Training of SVR:
        the SVR is trained by gradient decent using squared error as cost function, with proper normaliztion.
        the tarined model is then used to predict the next year rainfall and value is returned as a list, month-wise, consecutively.
       
    Visualizing data:
        A python source file is also included for graphical plotting of the data provided and predicted value.
    
thank you for reading

