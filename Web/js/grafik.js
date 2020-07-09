var nilai = [
	{x: '2020-7-7 15:00:13', y: '0'}, 
	{x: '2020-7-7 15:00:05', y: '0'},
	{x: '2020-7-7 15:00:10', y: '0'}, 
	{x: '2020-7-7 15:00:15', y: '0'},
	{x: '2020-7-7 15:00:20', y: '0'}, 
	{x: '2020-7-7 15:00:25', y: '0'},
	{x: '2020-7-7 15:00:30', y: '0'}, 
	{x: '2020-7-7 15:00:35', y: '0'}
];

function data(waktu, nilaibaru) {
	//hapus array pertama pada nilai dan masukan nilai waktu dan nilai baru pada array terakir
	for (let index = 0; index < nilai.length; index++) {
		nilai[index] = nilai[index+1];
	}

	nilai[7] = {            
		x: waktu,
		y: nilaibaru
	}
	//console.log(nilai);
	return nilai;
}

var graph = Morris.Line({
	element: 'chart',
	data: nilai,
	xkey: 'x',
	ykeys: ['y'],
	labels: ['nilai'],
	hideHover: true
});

function get_date(){
	date = new Date().toLocaleString();
	date = date.split(',');
	var tanggal = date[0].split('/');
	var date = tanggal[2] + '-' + tanggal [0] + '-' + tanggal [1] + date[1].slice(0, -3);
	return date;
}

