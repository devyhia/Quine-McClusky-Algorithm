require './lib/quine/minterm'
class HomeController < ApplicationController
  def index
  	if request.post?
  		@res = Quine.new.optimize(
  			params[:mins].split(',').map { |str| str.to_i }, 
  			params[:dcs].split(',').map { |str| str.to_i })
  		# render json: @res
  	end
  end
end
