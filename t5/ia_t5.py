from matplotlib.pyplot import plot
import numpy as np

from neupy import environment, algorithms, layers, plots

from sklearn import metrics
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder, MinMaxScaler

import theano

theano.config.floatX = 'float32'

digitos = np.loadtxt('exdata.csv', delimiter=',')

# Remove o valor que representa a classifição do digito, ou seja, remove a
# última linha da matriz de dados lida. O ".T" é responsável por transpor a
# matriz de dados
data = digitos[:-1].T

# Extrai as classificações dos dígitos representados no arquivo de dados.
target = digitos[-1]

# Procurar pelos valores de classificação igual a 10 e mapeá-los para 0.
target[target == 10] = 0

# Normalização dos dados será realizada utilizando o StandartScaler do 
# scikit-learn, que é uma API de análise de dados em python.
# Será utlizado o método "fit_transform" da classe StandartScaler, para
# realizar a normalização, que utiliza o cálculo da média e do desvio padrão.
# Para mais informações:
# http://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.StandardScaler.html
min_max_scaler = MinMaxScaler()
# standart_scaler = StandardScaler()
# scaler = StandardScaler()
data = min_max_scaler.fit_transform(data)
# dados_normalizados2 = standart_scaler.fit_transform(dados)

target_scaler = OneHotEncoder()
target = target_scaler.fit_transform(target.reshape((-1, 1)))
target = target.todense()

environment.reproducible()

data_train, data_test, target_train, target_test = train_test_split(
    data,
    target,
    train_size=(6. / 7),
    test_size=(1. / 7)
)

network = algorithms.Momentum(
    [
        layers.Input(400),
        layers.Relu(32),
        layers.Relu(300),
        layers.Softmax(10),
    ],
    error='categorical_crossentropy',
    step=0.01,
    verbose=True,
    shuffle_data=True,
    momentum=0.99,
    nesterov=True,
)

network.architecture()

network.train(data_train, target_train, data_test, target_test, epochs=20)

plots.error_plot(network)

target_predicted = network.predict(data_test).argmax(axis=1)
target_test = np.asarray(target_test.argmax(axis=1)).reshape(len(target_test))
print(metrics.classification_report(target_test, target_predicted))

score = metrics.accuracy_score(target_test, target_predicted)
print("Validation accuracy: {:.2%}".format(score))