class CreditsController < ApplicationController
def create
    @bank = Bank.find(params[:bank_id])
    @credit = @bank.credits.create(params[:credit_by])
    redirect_to bank_path(@bank)
  end
end
