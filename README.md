Projeto Irrigação
      Esse projeto é um protótipo de um sistema de irrigação inteligente que preserva o meio ambiente, já que utiliza a água se necessário para irrigar a plantação.
Para o Projeto serão usados os seguintes componentes:
1 Arduino UNO + Fonte Alimentação 9V2 Módulo Rele
1 Módulo Sensor de Umidade do Solo Higrômetro
 1 Módulo RTC  DS1302

1 Servo Motor

1 Válvula Solenóide


1 Mini Protoboard e Botão


Cabos Wire Jumper
1 Fonte alimentação 5V
1 Caixa de PVC para armazenar os componentesO Projeto
	 O sistema proposto funciona da seguinte forma: Através do Módulo Sensor de Umidade do Solo Higrômetro ligado ao ARDUINO podemos detectar as variações de umidade no solo, sendo que quando o solo está seco a saída do sensor fica em estado alto, e quando úmido em estado baixo. Com isso caso o solo necessite de água podemos acionar em horário programado com a ajuda do Módulo RTC DS1302 a válvula solenóide ou o servo motor que abre o registro.(a opção da inclusão do Servo Motor foi feito porque em alguns locais a água não é limpa e isso entope a válvula solenóide.)
	Existe a necessidade que no projeto tenha 3 reles, para o simples fato que o mesmo equipamento pode ser utilizado para irrigar varias áreas, onde algumas plantações requerem mais água que outras.
	Caso falte energia elétrica o sistema mantém a data e à hora atualizada com ajuda de uma bateria contida no Módulo RTC DS1302.
	Não vou abordar aqui o processo de construção do hardware (de cada módulo e suas determinadas ligações elétricas), já que isso se encontra facilmente na internet, basta uma simples pesquisa sobre cada módulo, mas o código fonte do projeto será disponibilizado. 
	Abaixo segue uma imagem de como ficou a montagem:



Melhorias no projeto
Pensando em IOT, é possível implementar o módulo ESP8266 para permitir que faça um acompanhamento on-line, com relatórios, ativações a distância e etc.., enfim podemos fazer muitas coisas.



